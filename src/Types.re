type reference = {
  uri: string,
  start: (string, int),
  stop: (string, int),
  text: string,
};

let newId = () =>
  Js.Math.random()
  ->Js.Float.toStringWithRadix(~radix=36)
  ->Js.String2.sliceToEnd(~from=2);

module Study = {
  type t = {
    id: string,
    title: string,
    created: float,
    finished: Set.String.t,
  };
  let empty = {
    id: "default",
    title: "Default",
    created: 0.,
    finished: Set.String.empty,
  };
};

module Annotation = {
  [@migrate.study a => "default"]
  type t = {
    id: string,
    study: string,
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
    modified: Js.Date.now(),
  };

  let isValid = ann => ann.references != [];

  let empty = {
    id: "",
    study: "",
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
  // let create = (~tags, ~references, ~notes) => {
  //   id: newId(),
  //   tags,
  //   references,
  //   notes,
  //   created: Js.Date.now(),
  //   modified: Js.Date.now(),
  // };
};

module Tag = {
  [@migrate.study t => "default"]
  type t = {
    id: string,
    study: string,
    name: string,
    color: string,
  };

  let create = (~name, ~color, ~study) => {id: newId(), name, color, study};
};

type state = {
  study: Study.t,
  annotations: Map.String.t(Annotation.t),
  tags: Map.String.t(Tag.t),
  current: Annotation.t,
};

let empty = {
  study: Study.empty,
  annotations: Map.String.empty,
  tags: Map.String.empty,
  current: Annotation.empty,
};