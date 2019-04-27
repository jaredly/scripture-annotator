type _localforage;

[@bs.val] [@bs.module "localforage"]
external createInstance: {. "name": string} => _localforage = "";

[@bs.send] external keys: _localforage => Js.Promise.t(array(string)) = "";
let keys = ((l, _, _)) => keys(l);

[@bs.send]
external setItem: (_localforage, string, 'v) => Js.Promise.t(unit) = "";

[@bs.send] external getItem: (_localforage, string) => Js.Promise.t('v) = "";

[@bs.send]
external removeItem: (_localforage, string) => Js.Promise.t(unit) = "";
let removeItem = ((l, _, _), id) => removeItem(l, id);

type localforage('t) = (
  _localforage,
  't => Js.Json.t,
  Js.Json.t => Result.t('t, list(string)),
);

[@bs.new] external error: 'a => Js.Exn.t = "Error";

let getItem = ((l, _pack, unpack): localforage('a), key): Js.Promise.t('a) => {
  let%Lets.Async raw = getItem(l, key);
  let json = Js.Json.parseExn(raw);
  switch (unpack(json)) {
  | Error(e) => Js.Promise.reject(Failure(e |> String.concat(":")))
  | Ok(v) => Js.Promise.resolve(v)
  };
};

let setItem =
    ((l, pack, _unpack): localforage('a), key, v: 'a): Js.Promise.t(unit) =>
  setItem(l, key, Js.Json.stringify(pack(v)));

let getAll = (l: localforage('a), getId: 'a => string) => {
  let%Lets.Async keys = keys(l);
  let%Lets.Async allItems =
    Js.Promise.all(
      keys->Array.map(key => l->getItem(key)->Lets.Async.orNone),
    );
  Lets.Async.resolve(
    Map.String.fromArray(
      allItems->Array.keepMap(item =>
        switch (item) {
        | None => None
        | Some(item) => Some((getId(item), item))
        }
      ),
    ),
  );
};

let annotationDb = (
  createInstance({"name": "annotations"}),
  TypeSerde.serializeAnnotation,
  TypeSerde.deserializeAnnotation,
);
let tagsDb = (
  createInstance({"name": "tags"}),
  TypeSerde.serializeTag,
  TypeSerde.deserializeTag,
);

let load = () => {
  let%Lets.Async (annotations, tags) =
    Js.Promise.all2((
      annotationDb->getAll(annotation => annotation.id),
      tagsDb->getAll(tag => tag.id),
    ));
  Lets.Async.resolve({
    Types.annotations,
    tags,
    current: Types.Annotation.empty,
  });
};

let settingsDb = (
  createInstance({"name": "settings"}),
  TypeSerde.serializeSettings,
  TypeSerde.deserializeSettings,
);
let loadSettings = () => settingsDb->getItem("default");
let saveSettings = settingsDb->setItem("default");