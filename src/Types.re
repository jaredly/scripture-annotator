type reference = {
  uri: string,
  start: (string, int),
  stop: (string, int),
};

let newId = () =>
  Js.Math.random()
  ->Js.Float.toStringWithRadix(~radix=36)
  ->Js.String2.sliceToEnd(~from=2);

module Annotation = {
  type t = {
    id: string,
    tags: list(string),
    references: list(reference),
    notes: string,
    created: float,
    modified: float,
  };

  let prepare = ann => {
    ...ann,
    id: ann.id == "" ? newId() : ann.id,
    created: ann.created == 0. ? Js.Date.now() : ann.created,
    modified: Js.Date.now()
  };

  let isValid = ann => ann.references != [];

  let empty = {
    id: "",
    tags: [],
    references: [],
    notes: "",
    created: 0.,
    modified: 0.,
  };

  let clone = annotation => {
    ...annotation,
    id: newId(),
    created: Js.Date.now(),
    modified: Js.Date.now(),
  };

  let clear = annotation => {
    ...annotation,
    id: "",
    notes: "",
    references: [],
    created: 0.,
    modified: 0.,
  };

  let create = (~tags, ~references, ~notes) => {
    id: newId(),
    tags,
    references,
    notes,
    created: Js.Date.now(),
    modified: Js.Date.now(),
  };
};

module Tag = {
  type t = {
    id: string,
    name: string,
    color: string,
  };

  let create = (~name, ~color) => {id: newId(), name, color};
};

type state = {
  annotations: Map.String.t(Annotation.t),
  tags: Map.String.t(Tag.t),
  current: Annotation.t,
};