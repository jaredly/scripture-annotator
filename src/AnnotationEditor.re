let str = React.string;

module Styles = {
  open Css;
};

[@react.component]
let make = (~uri, ~onChange, ~state as {Types.annotations, tags, current as annotation}, ~onSave, ~onClear) => {
  <div>
    <BlurInput
      value={annotation.notes}
      onChange={notes => onChange({...annotation, notes})}
    />
    {annotation.references->List.map(({uri, start, stop}) => (
      <button onClick={(_evt) => {
        Web.Selection.current()->Web.Selection.fromIdOffset(start, stop)
      }}>
        // {React.string(uri)}
        {React.string(fst(start) ++ ":" ++ fst(stop))}
      </button>
    ))->List.toArray->React.array}
    <button
      disabled={!annotation->Types.Annotation.isValid}
      onClick={evt => onSave()}>
      {str("Save")}
    </button>
    <button onClick={evt => onClear()}> {str("Cancel")} </button>
    <button onClick={evt => {
      let s = Web.Selection.current();
      let%Lets.OptConsume (start, stop) = s->Web.Selection.toIdOffset;
      onChange({
        ...annotation,
        references: annotation.references @ [{
          uri,
          start,
          stop,
        }]
      })
      Js.log2(start, stop)
    }}>
      {React.string("Add selection")}
    </button>
  </div>;
};