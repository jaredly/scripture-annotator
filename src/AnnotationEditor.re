let str = React.string;

module Styles = {
  open Css;
};

[@react.component]
let make = (~uri, ~onChange, ~state as {Types.annotations, tags, current as annotation}, ~onSave, ~onClear) => {
  <div className=Css.(style([
    width(px(300))
  ]))>
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
    <button onClick={evt => {
      let s = Web.Selection.current();
      let%Lets.OptConsume (start, stop) = s->Web.Selection.toIdOffset;
      onChange({
        ...annotation,
        references: annotation.references @ [{
          uri,
          start,
          stop,
          text: s->Web.Selection.toString,
        }]
      })
      Js.log2(start, stop)
    }}>
      {React.string("Add selection")}
    </button>
    {annotation.references->List.mapWithIndex((i, ref) => {
      let {Types.uri, start, stop, text} = ref;
      <div onClick={(_evt) => {
        Web.Selection.current()->Web.Selection.fromIdOffset(start, stop)
      }} key={string_of_int(i)}>
        {React.string(fst(start) ++ ":" ++ fst(stop))}
        <div>
          {React.string(text)}
        </div>
        <button onClick={evt => {
          onChange({...annotation, references: annotation.references->List.keep(r => r != ref)})
          evt->ReactEvent.Mouse.stopPropagation;
        }}>
          {React.string("Remove")}
        </button>
      </div>
    })->List.toArray->React.array}
  </div>;
};