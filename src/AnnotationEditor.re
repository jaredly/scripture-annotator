
module Styles = {
  open Css;
};

[@react.component]
let make = (~state as {Types.annotations, tags}, ~onSave) => {
  let (annotation, update) = Hooks.useState(Types.Annotation.empty);

  <div>
    <BlurInput
      value={annotation.notes}
      onChange={notes => update({...annotation, notes})}
    />
  </div>
};