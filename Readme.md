
# New style, restricted game plan.
Goal: allow me to make some annotations. Those annotations will later be reworkable if needed, but let's just get something going.


Questions:

### How to store the data?
Let's extract from the db (by chapter) and then gzip it, and use `pako` on the browser side to unzip.
First pass: just do the new testament.

### What screens are needed?
Chapter view w/ ability to display & add annotations

### How will we store the annotations?
For now, let's do localForage maybe? Or leveljs?
yeah localforage seems fine.

<!-- type kind =
  | Tag(string)
  | Attribute(attribute) -->

```js

// type attribute = (string, string);
  // | Speaker(string)
  // | Date(string)

type reference = {
  uri: string,
  // (verse, word)
  start: (int, int),
  end: (int, int)
}

type annotation = {
  id: string,
  // let's try this, see how it goes
  tags: list(string),
  // Maybe add this in later if needed
  // an ID of the attribute, and the value (stringly typed for now)
  // attributes: list((string, string)),
  references: list(reference),
  notes: string,
  created: int,
  modified: int,
}

// type attribute = {
//   id: string,
//   name: string,
//   color: string,
// }

type tag = {
  id: string,
  name: string,
  color: string,
}

type state = {
  // probably combine these two into an opaque data structure
  annotations: Belt.Map.String.t(annotation),
  // will need to keep in sync yup
  // also probably don't event need this to start out
  // annotationByUri: Belt.Map.String.t(list(annotation)),
  tags: Belt.Map.String.t(tag),
  // attributes: Belt.Map.String.t(attribute),
}

```












