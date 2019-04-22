type reference = {
  uri: string,
  start: (int, int),
  stop: (int, int),
};

module Annotation = {
  type t = {
    id: string,
    tags: list(string),
    references: list(reference),
    notes: string,
    created: float,
    modified: float,
  };
};

module Tag = {
  type t = {
    id: string,
    name: string,
    color: string,
  };
};

type state = {
  annotations: Map.String.t(Annotation.t),
  tags: Map.String.t(Tag.t),
};