let str = React.string;

module Styles = {
  open Css;
};

[@react.component]
let make = (~onChange, ~state as {Types.annotations, tags, current as annotation}, ~onSave, ~onClear) => {
  <div>
    <BlurInput
      value={annotation.notes}
      onChange={notes => onChange({...annotation, notes})}
    />
    <button
      disabled={!annotation->Types.Annotation.isValid}
      onClick={evt => onSave()}>
      {str("Save")}
    </button>
    <button onClick={evt => onClear()}> {str("Cancel")} </button>
  </div>;
};