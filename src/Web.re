
[@bs.module "querystring"] external stringify: Js.t('a) => string = "";

[@bs.module "url"] external urlParse: (string, bool) => {. "query": Js.nullable({. "error": Js.nullable(string), "code": Js.nullable(string)})} = "parse";


type headers;
[@bs.send] external get: (headers, string) => string = "";

type response = {."headers": headers, "status": int};

[@bs.val] external fetch: (string, 'config) => Js.Promise.t(response) = "";
[@bs.send] external json: response => Js.Promise.t('a) = "";

module Location = {
  type t;
  [@bs.val] external location: t = "";
  [@bs.get] external hash: t => string = "";
  [@bs.set] external setHash: (t, string) => unit = "hash";
  let hash = () => location->hash;
  let setHash = hash => location->setHash(hash);
  type window;
  [@bs.val] external window: window = "";
  [@bs.send] external addEventListener: (window, string, ('event) => unit, bool) => unit = "";
  [@bs.send] external removeEventListener: (window, string, ('event) => unit, bool) => unit = "";
  let addHashListener = (fn) => {
    let listener = () => fn(hash());
    window->addEventListener("hashchange", listener, false);
    () => window->removeEventListener("hashchange", listener, false);
  };
};
