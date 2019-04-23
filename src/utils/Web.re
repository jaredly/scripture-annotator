
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
};

module Selection = {
  type t;
  [@bs.val] external getSelection: window => t = "";
  let current = () => window->getSelection;

  [@bs.get] external anchorNode: t => Dom.node = "";
  [@bs.get] external anchorOffset: t => int = "";
  [@bs.get] external extentNode: t => Dom.node = "";
  [@bs.get] external extentOffset: t => int = "";
  [@bs.send] external setBaseAndExtent: (t, Dom.node, int, Dom.node, int) => unit = "";

  let idOffsetToAnchor: (. Dom.node, int) => option((Dom.node, int)) = [%bs.raw {|
    function idOffsetToAnchor(node, offset) {
      // console.log("Looking", node, offset)
      if (node.nodeName === '#text') {
        return [node, offset]
      }
      for (let i = 0; i < node.childNodes.length; i++) {
        const child = node.childNodes[i];
        const length = child.textContent.length
        if (offset < length) {
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
  let fromIdOffset = (selection, (anchorId, aoff), (extentId, eoff)) => {
    module Opt = Lets.OptConsume;
    let%Opt (anchor, aoff) = fromSingleIdOffset((anchorId, aoff));
    let%Opt (extent, eoff) = fromSingleIdOffset((extentId, eoff));
    // let%Opt (extent, eoff) = idOffsetToAnchor(. extent, eoff);
    selection->setBaseAndExtent(anchor, aoff, extent, eoff);
  };

  let anchorToIdOffset: (. Dom.node, int) => option((string, int)) = [%bs.raw {|
  function getOffset(node, offset) {
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
    return getOffset(parent, offset)
  }
  |}];
  let toIdOffset = selection => {
    let%Lets.Opt anchor = anchorToIdOffset(. selection->anchorNode, selection->anchorOffset);
    let%Lets.Opt extent = anchorToIdOffset(. selection->extentNode, selection->extentOffset);
    if (fst(anchor) > fst(extent) || (fst(anchor) == fst(extent) && snd(anchor) > snd(extent))) {
      Some((extent, anchor))
    } else {
      Some((anchor, extent))
    }
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
