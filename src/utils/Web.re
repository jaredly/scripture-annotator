
[@bs.module "querystring"] external stringify: Js.t('a) => string = "";

[@bs.module "url"] external urlParse: (string, bool) => {. "query": Js.nullable({. "error": Js.nullable(string), "code": Js.nullable(string)})} = "parse";


type headers;
[@bs.send] external get: (headers, string) => string = "";

type response = {."headers": headers, "status": int};

[@bs.val] external fetch: (string, 'config) => Js.Promise.t(response) = "";
[@bs.send] external json: response => Js.Promise.t('a) = "";

type window;
[@bs.val] external window: window = "";
[@bs.val] external document: Dom.node = "";
[@bs.send] external addEventListener: (window, string, ('event) => unit, bool) => unit = "";
[@bs.send] external removeEventListener: (window, string, ('event) => unit, bool) => unit = "";
[@bs.send] external getElementById: (Dom.node, string) => option(Dom.node) = "";
type rect = {
  .
  "top": float,
  "height": float,
  "width": float,
  "left": float,
  "bottom": float,
  "right": float,
};
[@bs.send] external getBoundingClientRect: Dom.node => rect = "";

module Range = {
  type t;
  [@bs.send] external createRange: Dom.node => t = "";
  let createRange = () => document->createRange;
  [@bs.send] external setStart: (t, Dom.node, int) => unit = "";
  let setStart = (t, (node, off)) => setStart(t, node, off);
  [@bs.send] external setEnd: (t, Dom.node, int) => unit = "";
  let setEnd = (t, (node, off)) => setEnd(t, node, off);
  [@bs.send] external getBoundingClientRect: t => rect = "";
  [@bs.send] external collapse: (t, ~toStart: bool) => unit = "";
  [@bs.send] external cloneRange: t => t = "";

  let toHTML: t => string = [%bs.raw {|
  function (range) {
    return [...range.cloneContents().childNodes].map(child => child.outerHTML || child.textContent).join('')
  }
  |}];

  [@bs.get] external startContainer: t => Dom.node = "";
  [@bs.get] external startOffset: t => int = "";
  [@bs.get] external endContainer: t => Dom.node = "";
  [@bs.get] external endOffset: t => int = "";
  let start = r => (r->startContainer, r->startOffset);
  let end_ = r => (r->endContainer, r->endOffset);
};

module Selection = {
  type t;
  [@bs.val] external getSelection: window => t = "";
  let current = () => window->getSelection;

  [@bs.get] external anchorNode: t => Dom.node = "";
  [@bs.get] external anchorOffset: t => int = "";
  [@bs.get] external extentNode: t => Dom.node = "";
  [@bs.get] external extentOffset: t => int = "";
  [@bs.send] external toString: t => string = "";
  [@bs.send] external setBaseAndExtent: (t, Dom.node, int, Dom.node, int) => unit = "";

  [@bs.send] external getRangeAt: (t, int) => Range.t = "";
  let getRange = t => getRangeAt(t, 0);

  let anchor = selection => (selection->anchorNode, selection->anchorOffset);
  let extent = selection => (selection->extentNode, selection->extentOffset);

  let idOffsetToAnchor: (. Dom.node, int) => option((Dom.node, int)) = [%bs.raw {|
    function idOffsetToAnchor(node, offset) {
      // console.log("Looking", node, offset)
      if (node.nodeName === '#text') {
        return [node, offset]
      }
      for (let i = 0; i < node.childNodes.length; i++) {
        const child = node.childNodes[i];
        const length = child.textContent.length
        if (offset <= length) {
          return idOffsetToAnchor(child, offset)
        // } else {
        //   console.log("going past child", offset, length, child)
        }
        offset -= length
      }
      // console.log("ran out of childNodes", node, offset)
      return undefined
    }
  |}];
  let fromSingleIdOffset = ((nodeId, offset)) => {
    let%Lets.Opt anchor = document->getElementById(nodeId);
    let%Lets.Opt (anchor, offset) = idOffsetToAnchor(. anchor, offset);
    Some((anchor, offset))
  };
  let fromIdOffset = (selection, start, end_) => {
    module Opt = Lets.OptConsume;
    let%Opt (anchor, aoff) = fromSingleIdOffset(start);
    let%Opt (extent, eoff) = fromSingleIdOffset(end_);
    selection->setBaseAndExtent(anchor, aoff, extent, eoff);
  };

  let adjustForWordBoundaries: (. (Dom.node, int), bool) => (Dom.node, int) = [%bs.raw {|
  function ([node, offset], back) {
    const text = node.textContent
    console.log('checking', back, text.slice(0, offset), text.slice(offset))
    if (back) {
      const before = text.slice(0, offset).match(/\w+$/)
      if (before) {
        console.log(before)
        offset -= before[0].length
      }
      return [node, offset]
    } else {
      const after = text.slice(offset).match(/^\w+/)
      if (after) {
        console.log(after)
        offset += after[0].length
      }
      return [node, offset]
    }
  }
  |}];
  let adjustForWordBoundaries = (noff, back) => adjustForWordBoundaries(. noff, back);

  let adjustSelection = selection => {
    let range = selection->getRange;
    open Range;
    let (snode, soff) = range->start->adjustForWordBoundaries(true);
    let (enode, eoff) = range->end_->adjustForWordBoundaries(false);
    selection->setBaseAndExtent(
      snode,
      soff,
      enode,
      eoff
    );
  };

  let findVerse: (. Dom.node) => option(Dom.node) = [%bs.raw {|
  function findVerse(node) {
    if (node.className === 'verse' && node.id) {
      return node
    }
    const parent = node.parentNode
    if (!parent || parent === document.body) {
      return undefined
    }
    return findVerse(parent)
  }
  |}];
  let findVerse = m => findVerse(. m);

  let expandToEncompass: (. t, Dom.node, Dom.node) => unit = [%bs.raw {|
  function (selection, start, end) {
    if (start === end) {
      selection.getRangeAt(0).selectNodeContents(start)
      return
    }
    let srange = document.createRange()
    srange.selectNodeContents(start);
    let erange = document.createRange()
    erange.selectNodeContents(end);
    selection.setBaseAndExtent(
      srange.startContainer,
      srange.startOffset,
      erange.endContainer,
      erange.endOffset
    );
  }
  |}];

  let anchorToIdOffset: (. (Dom.node, int)) => option((string, int)) = [%bs.raw {|
  function getOffset([node, offset]) {
    if (node.className === 'verse' && node.id) {
      return [node.id, offset]
    }
    const parent = node.parentNode
    if (!parent || parent === document.body) {
      return undefined
    }
    node = node.previousSibling
    while (node) {
      offset += node.textContent.length
      node = node.previousSibling
    }
    return getOffset([parent, offset])
  }
  |}];
  let toIdOffset = (selection, fullVerses) => {
    if (fullVerses) {
      let range = selection->getRange;
      let%Lets.OptConsume sverse = range->Range.startContainer->findVerse;
      let%Lets.OptConsume everse = range->Range.endContainer->findVerse;
      expandToEncompass(. selection, sverse, everse)
    } else {
      selection->adjustSelection;
    };
    let range = selection->getRange;
    open Range;
    let%Lets.Opt start = anchorToIdOffset(. range->start);
    let%Lets.Opt end_ = anchorToIdOffset(. range->end_);
    Some((start, end_))
  };
};

module Location = {
  type t;
  [@bs.val] external location: t = "";
  [@bs.get] external hash: t => string = "";
  [@bs.set] external setHash: (t, string) => unit = "hash";
  let hash = () => location->hash;
  let setHash = hash => location->setHash(hash);
  let addHashListener = (fn) => {
    let listener = () => fn(hash());
    window->addEventListener("hashchange", listener, false);
    () => window->removeEventListener("hashchange", listener, false);
  };
};
