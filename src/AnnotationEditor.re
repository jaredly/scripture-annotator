let str = React.string;

module Styles = {
  open Css;
};

[@react.component]
let make =
    (
      ~uri,
      ~onChange,
      ~state as {Types.annotations, tags, current as annotation},
      ~onSave,
      ~onClear,
    ) => {
  <div className=Css.(style([width(px(300))]))>
    <div className=Css.(style([flexDirection(`row)]))>
      <button
        disabled={!annotation->Types.Annotation.isValid}
        onClick={evt => onSave()}>
        {str("Save")}
      </button>
      <button onClick={evt => onClear()}> {str("Cancel")} </button>
      <button
        onClick={evt => {
          let s = Web.Selection.current();
          let%Lets.OptConsume (start, stop) = s->Web.Selection.toIdOffset;
          onChange({
            ...annotation,
            references:
              annotation.references
              @ [
                {
                  uri,
                  start,
                  stop,
                  text: s->Web.Selection.getRange->Web.Range.toHTML,
                },
              ],
          });
          Js.log2(start, stop);
        }}>
        {React.string("Add selection")}
      </button>
    </div>
    <BlurTextArea
      value={annotation.notes}
      onChange={notes => onChange({...annotation, notes})}
    />
    {annotation.references
     ->List.mapWithIndex((i, ref) => {
         let {Types.uri, start, stop, text} = ref;
         <div
           onClick={_evt =>
             Web.Selection.current()->Web.Selection.fromIdOffset(start, stop)
           }
           key={string_of_int(i)}
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
                 margin2(~h=`zero, ~v=px(8)),
               ])
             )
             dangerouslySetInnerHTML={"__html": text}
           />
           <button
             onClick={evt => {
               onChange({
                 ...annotation,
                 references: annotation.references->List.keep(r => r != ref),
               });
               evt->ReactEvent.Mouse.stopPropagation;
             }}>
             {React.string("Remove")}
           </button>
         </div>;
       })
     ->List.toArray
     ->React.array}
  </div>;
};