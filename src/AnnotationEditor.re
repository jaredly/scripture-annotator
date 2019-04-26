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
      className=Css.(style([marginBottom(px(16)),
      boxShadow(~blur=px(3), hex("ccc")),
      padding(px(8)),
      ]))>
      <div className=Css.(style([flexDirection(`row), justifyContent(`spaceBetween)]))>
        {React.string(
           {let start = fst(start)
            let end_ = fst(stop)
            if (start == end_) {
              start;
            } else {
              start ++ "-" ++ end_;
            }},
         )}
        <button
          onClick={evt => {
            evt->ReactEvent.Mouse.stopPropagation;
            onRemove();
          }}>
          {React.string("Remove")}
        </button>
      </div>
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
      ~onDelete,
      ~addSelection,
      ~onClear,
      ~onAddTag,
      ~onCreateTag,
      ~onRemoveTag,
    ) => {
  <div className=Css.(style([width(px(300)), marginLeft(px(16)), paddingTop(px(16))]))>
    <div className=Css.(merge([SharedStyles.smallHeader, style([
      marginBottom(px(16))
    ])]))>
      {React.string(annotation.id != "" ? "Update entry" : "Add entry")}
    </div>
    <div className=Css.(style([flexDirection(`row)]))>
      <button
        disabled={!annotation->Types.Annotation.isValid}
        onClick={evt => onSave()}>
        {str("Save")}
      </button>
      <button
        disabled={!annotation->Types.Annotation.isValid}
        onClick={evt => {onSave(); onClear()}}>
        {str("Save & Clear")}
      </button>
      <button onClick={evt => onClear()}> {str("Cancel")} </button>
      <button
      disabled={annotation.id == ""}
      onClick={evt => onDelete()}> {str("Delete")} </button>
    </div>
    <div className=Css.(merge([SharedStyles.label, style([
      marginBottom(px(8)),
      marginTop(px(16)),
    ])]))>
    {str("Notes")}
    </div>
    <BlurTextArea
      value={annotation.notes}
      className=Css.(style([
        marginBottom(px(16)),
        padding2(~v=px(8), ~h=px(8)),
        fontSize(px(20)),
        fontWeight(`extraLight),
      ]))
      onChange={notes => onChange({...annotation, notes})}
    />
    <TagsEditor
      tags
      current={annotation.tags}
      onCreate=onCreateTag
      onAdd=onAddTag
      onRemove=onRemoveTag
    />
    <div
    className=Css.(merge([SharedStyles.label, style([
      marginBottom(px(8)),
      marginTop(px(16)),
    ])]))
    > {str("Annotations")} </div>
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