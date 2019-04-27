module Styles = {
  open Css;
  let noTags = style([fontStyle(`italic), fontSize(`percent(80.))]);
  let tags =
    style([
      flexDirection(`row),
      padding2(~v=px(8), ~h=`zero),
      flexWrap(`wrap),
    ]);
  let tag =
    style([
      flexDirection(`row),
      padding2(~v=px(4), ~h=px(8)),
      borderRadius(px(4)),
      marginRight(px(8)),
      marginBottom(px(4)),
    ]);
  let closeButton =
    style([
      borderStyle(`none),
      cursor(`pointer),
      backgroundColor(`transparent),
      marginRight(px(-4)),
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
  let reduce = ((text, focused), action) =>
    switch (action) {
    | `Text(text) => (text, 0)
    | `Focused(focused) => (text, focused)
    };
  [@react.component]
  let make = (~getItems, ~renderItem, ~placeholder, ~autoFocus=?) => {
    let ((newText, selected), dispatch) =
      React.useReducer(reduce, ("", 0));
    let (focused, setFocused) = Hooks.useState(false);
    let items =
      React.useMemo2(() => getItems(newText), (newText, getItems));
    <div className=Css.(style([position(`relative)]))>
      <input
        value=newText
        placeholder
        ?autoFocus
        onFocus={evt => setFocused(true)}
        onBlur={evt => setFocused(false)}
        onChange={evt => {
          let text = evt->ReactEvent.Form.target##value;
          dispatch(`Text(text));
        }}
        onKeyDown={evt =>
          switch (evt->ReactEvent.Keyboard.key) {
          | "ArrowUp" =>
            evt->ReactEvent.Keyboard.preventDefault;
            dispatch(
              `Focused(
                selected <= 0 ? Array.length(items) - 1 : selected - 1,
              ),
            );
          | "Escape" => dispatch(`Text(""))
          | "Enter" =>
            evt->ReactEvent.Keyboard.preventDefault;
            let%Lets.OptConsume item = items[selected];
            item.action();
            dispatch(`Text(""));
          | "ArrowDown" =>
            evt->ReactEvent.Keyboard.preventDefault;
            dispatch(
              `Focused(
                selected >= Array.length(items) - 1 ? 0 : selected + 1,
              ),
            );
          | _ => ()
          }
        }
        className=Css.(style([padding(px(8))]))
      />
      {focused
         ? <div
             className=Css.(
               style([
                 position(`absolute),
                 top(`percent(100.)),
                 zIndex(100),
                 maxHeight(px(400)),
                 overflow(`auto),
                 maxWidth(px(300)),
                 backgroundColor(white),
                 boxShadow(~y=px(2), ~blur=px(5), hex("ccc")),
               ])
             )>
             {items
              ->Array.mapWithIndex((i, {action, contents}) =>
                  <div
                    key={string_of_int(i)}
                    className=Css.(
                      style([
                        flexShrink(0),
                        hover([backgroundColor(hex("eee"))]),
                        backgroundColor(
                          i == selected ? hex("eee") : transparent,
                        ),
                        cursor(`pointer),
                        padding2(~v=px(8), ~h=px(16)),
                      ])
                    )
                    onMouseDown={evt => action()}>
                    {renderItem(contents)}
                  </div>
                )
              ->React.array}
           </div>
         : React.null}
    </div>;
  };
};

module TagEditor = {
  [@react.component]
  let make = (~tag as orig: Types.Tag.t, ~onClose, ~onSave) => {
    let (tag, update) = Hooks.useState(orig);
    <Modal onClose>
      <div
        className=Css.(
          style([
            backgroundColor(white),
            padding(px(8)),
            borderRadius(px(4)),
          ])
        )
      >
        <BlurInput
          value={tag.name}
          onChange={name => update({...tag, name})}
        />
        <BlurInput
          value={tag.color}
          onChange={color => update({...tag, color})}
        />
        <button
          disabled={tag == orig}
          onClick={evt => onSave(tag)}
        >
          {React.string("Save")}
        </button>
        <button
          onClick={evt => onClose()}
        >
          {React.string("Close")}
        </button>
      </div>
    </Modal>;
  };
};

[@react.component]
let make =
    (
      ~tags: Map.String.t(Types.Tag.t),
      ~current,
      ~onChange,
      ~onCreate,
      ~onAdd,
      ~onRemove,
    ) => {
  let (editingTag, setEditingTag) = Hooks.useState(None);
  let getItems =
    React.useMemo1(
      ((), newText) =>
        newText == ""
          // TODO recent tags
          ? tags
            ->Map.String.valuesToArray
            ->Array.map(tag =>
                {contents: `Tag(tag), action: () => onAdd(tag.id)}
              )
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
    {switch (editingTag) {
     | None => React.null
     | Some(tag) =>
       <TagEditor
         tag
         onClose={() => setEditingTag(None)}
         onSave={tag => onChange(tag)}
       />
     }}
    <div className=Styles.tags>
      {current == []
         ? <div className=Styles.noTags> {React.string("No tags")} </div>
         : current
           ->List.toArray
           ->Array.keepMap(id => {
               let%Lets.OptWrap tag = tags->Map.String.get(id);
               <div
                 className=Styles.tag
                 key={tag.id}
                 onClick={_evt => {
                   setEditingTag(Some(tag))
                 }}
                 style={ReactDOMRe.Style.make(~backgroundColor=tag.color, ())}>
                 {React.string(tag.name)}
                 <button
                   onClick={evt => {
                     evt->ReactEvent.Mouse.stopPropagation;
                     onRemove(tag.id)
                    }}
                   className=Styles.closeButton>
                   {React.string("x")}
                 </button>
               </div>;
             })
           ->React.array}
    </div>
    <Autocomplete
      placeholder="Add a tag"
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