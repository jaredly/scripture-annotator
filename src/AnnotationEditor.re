let str = React.string;

module Styles = {
  open Css;
};

module Reference = {
  [@react.component]
  let make = (~reference, ~onRemove) => {
    let {Types.uri, start, stop, text} = reference;
    <div
      onClick={_evt =>
        Web.Selection.current()->Web.Selection.fromIdOffset(start, stop)
      }
      className=Css.(style([marginBottom(px(16))]))>
      {React.string(
         {let start = fst(start)
          let end_ = fst(stop)
          if (start == end_) {
            start;
          } else {
            start ++ "-" ++ end_;
          }},
       )}
      <div
        className=Css.(
          style([
            fontSize(`percent(80.)),
            display(`block),
            margin2(~h=`zero, ~v=px(8)),
          ])
        )
        dangerouslySetInnerHTML={"__html": text}
      />
      <button
        onClick={evt => {
          evt->ReactEvent.Mouse.stopPropagation;
          onRemove();
        }}>
        {React.string("Remove")}
      </button>
    </div>;
  };
};

[@react.component]
let make =
    (
      ~uri,
      ~onChange,
      ~state as {Types.annotations, tags, current as annotation},
      ~onSave,
      ~addSelection,
      ~onClear,
      ~onAddTag,
      ~onCreateTag,
      ~onRemoveTag,
    ) => {
  <div className=Css.(style([width(px(300))]))>
    <div className=Css.(style([flexDirection(`row)]))>
      <button
        disabled={!annotation->Types.Annotation.isValid}
        onClick={evt => onSave()}>
        {str("Save")}
      </button>
      <button onClick={evt => onClear()}> {str("Cancel")} </button>
      <button onClick={evt => addSelection(false)}>
        {React.string("Add selection")}
      </button>
    </div>
    {str("Notes")}
    <BlurTextArea
      value={annotation.notes}
      onChange={notes => onChange({...annotation, notes})}
    />
    {str("Tags")}
    <TagsEditor
      tags
      current=annotation.tags
      onCreate=onCreateTag
      onAdd=onAddTag
      onRemove=onRemoveTag
    />
    <div>
      {str("Annotations")}
    </div>
    {annotation.references
     ->List.mapWithIndex((i, ref) =>
         <Reference
           reference=ref
           onRemove={() =>
             onChange({
               ...annotation,
               references: annotation.references->List.keep(r => r != ref),
             })
           }
           key={string_of_int(i)}
         />
       )
     ->List.toArray
     ->React.array}
  </div>;
};