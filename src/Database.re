
type _localforage;

[@bs.val]
[@bs.module "localforage"]
external createInstance: ({. "name": string}) => _localforage = "";

[@bs.send]
external keys: _localforage => Js.Promise.t(array(string)) = "";

[@bs.send]
external setItem: (_localforage, string, 'v) => Js.Promise.t(unit) = "";

[@bs.send]
external getItem: (_localforage, string) => Js.Promise.t('v) = "";

type localforage('t) = _localforage;

let getItem = (l: localforage('a), key): Js.Promise.t('a) => getItem(l, key);
let setItem = (l: localforage('a), key, v: 'a): Js.Promise.t(unit) => setItem(l, key, v);

let getAll = (l: localforage('a), getId: 'a => string) => {
  let%Lets.Async keys = keys(l);
  let%Lets.Async allItems = Js.Promise.all(keys->Array.map(key => getItem(l, key)));
  Lets.Async.resolve(Map.String.fromArray(allItems->Array.map(item => (getId(item), item))))
};
