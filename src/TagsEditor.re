module Styles = {
  open Css;
  let tags = style([flexDirection(`row), padding(px(8)),
  flexWrap(`wrap)
  ]);
  let tag =
    style([
      padding2(~v=px(4), ~h=px(8)),
      borderRadius(px(4)),
      marginRight(px(4)),
      marginBottom(px(4)),
    ]);
};

type autocomplete('contents) = {
  action: unit => unit,
  contents: 'contents,
};

let matchingTags = (tags: Map.String.t(Types.Tag.t), text) => {
  let needle = text->Js.String.toLowerCase;
  let found =
    tags
    ->Map.String.valuesToArray
    ->Array.keepMap(tag => {
        let name = tag.name->Js.String.toLowerCase;
        if (Fuzzy.fuzzysearch(needle, name)) {
          Some(Fuzzy.wrap(tag, Fuzzy.fuzzyScore(needle, name)));
        } else {
          None;
        };
      })
    ->Js.Array.sortInPlaceWith(Fuzzy.sort, _)
    ->Array.map(m => m.contents);
  found;
};

module Autocomplete = {
  let reduce = ((text, focused), action) => switch action {
    | `Text(text) => (text, 0)
    | `Focused(focused) => (text, focused)
  };
  [@react.component]
  let make = (~getItems, ~renderItem) => {
    let ((newText, selected), dispatch) = React.useReducer(reduce, ("", 0));
    let (focused, setFocused) = Hooks.useState(false);
    let items =
      React.useMemo2(() => getItems(newText), (newText, getItems));
    <div className=Css.(style([
      position(`relative)
    ]))>
      <input
        value=newText
        onFocus={evt => setFocused(true)}
        onBlur={evt => setFocused(false)}
        onChange={evt => {
          let text = evt->ReactEvent.Form.target##value;
          dispatch(`Text(text));
        }}
        onKeyDown={evt => {
          switch (evt->ReactEvent.Keyboard.key) {
            | "ArrowUp" =>
            evt->ReactEvent.Keyboard.preventDefault;
            dispatch(`Focused(selected <= 0 ? Array.length(items) - 1 : selected - 1))
            | "Escape" =>
              dispatch(`Text(""))
            | "Enter" =>
            evt->ReactEvent.Keyboard.preventDefault;
            let%Lets.OptConsume item = items[selected];
            item.action();
            dispatch(`Text(""))
            | "ArrowDown" =>
            evt->ReactEvent.Keyboard.preventDefault;
            dispatch(`Focused(selected >= Array.length(items) - 1 ? 0 : selected + 1))
            | _ => ()
          }
        }}
        className=Css.(style([
          padding(px(8)),
        ]))
      />
      {focused
      ? <div className=Css.(style([
        position(`absolute),
        top(`percent(100.)),
        maxHeight(px(400)),
        maxWidth(px(300)),
        backgroundColor(white),
        boxShadow(~y=px(2), ~blur=px(5), hex("ccc"))
      ]))>
        {items
         ->Array.mapWithIndex((i, {action, contents}) =>
             <div
             key={string_of_int(i)}
             className=Css.(style([
               hover([
                 backgroundColor(hex("eee"))
               ]),
               backgroundColor(i == selected ? hex("eee") : transparent),
               cursor(`pointer),
               padding2(~v=px(8), ~h=px(16))
             ]))
             onMouseDown={evt => action()}> {renderItem(contents)} </div>
           )
         ->React.array}
      </div>
      : React.null}
    </div>;
  };
};

[@react.component]
let make =
    (
      ~tags: Map.String.t(Types.Tag.t),
      ~current,
      ~onCreate,
      ~onAdd,
      ~onRemove,
    ) => {
  let getItems =
    React.useMemo1(
      ((), newText) =>
        newText == ""
        // TODO recent tags
          ? tags->Map.String.valuesToArray->Array.map(tag => {contents: `Tag(tag), action: () => onAdd(tag.id)})
          : {
            let found =
              tags
              ->matchingTags(newText)
              ->Array.map(tag =>
                  {contents: `Tag(tag), action: () => onAdd(tag.id)}
                );
            found->Array.concat([|
              {contents: `New(newText), action: () => onCreate(newText)},
            |]);
          },
      [|tags|],
    );

  <div>
    <div className=Styles.tags>
      {current == []
         ? React.string("No tags")
         : current
           ->List.toArray
           ->Array.keepMap(id => {
               let%Lets.OptWrap tag = tags->Map.String.get(id);
               <div
                 className=Styles.tag
                 key={tag.id}
                 style={ReactDOMRe.Style.make(~backgroundColor=tag.color, ())}>
                 {React.string(tag.name)}
               </div>;
             })
           ->React.array}
    </div>
    <Autocomplete
      renderItem={item =>
        switch (item) {
        | `Tag((tag: Types.Tag.t)) => React.string(tag.name)
        | `New(text) => React.string("Create new tag: " ++ text)
        }
      }
      getItems
    />
  </div>;
};