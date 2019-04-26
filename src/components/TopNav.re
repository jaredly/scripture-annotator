let navigateTo = (volume, item) =>
  Web.Location.setHash(volume##uri ++ ":" ++ item##uri);

let getSiblings = (nav, volume, content) => {
  let%Lets.Opt nav = nav->Js.Dict.get(volume##item_id);
  let%Lets.Opt index =
    nav##nav
    ->Array.getIndexBy(item => item##subitem_id == content##subitem_id);
  Some((nav##nav[index - 1], nav##nav[index + 1]));
};

[@react.component]
let make = (~nav, ~volume, ~content) => {
  let getItems =
    React.useCallback1(
      text => {
        let allItems =
          nav
          ->Js.Dict.values
          ->Array.map(volume => volume##nav->Array.map(nav => (volume, nav)))
          ->Array.concatMany;
        let text = text->Js.String.toLowerCase;
        allItems
        ->Array.keepMap(((volume, item)) => {
            let title =
              Fuzzy.fuzzysearch(text, item##title->Js.String.toLowerCase);
            // let subtitle = Fuzzy.fuzzysearch(text, item##subtitle->Js.String.toLowerCase);
            if (title) {
              Some(
                Fuzzy.wrap(
                  (volume, item),
                  Fuzzy.fuzzyScore(text, item##title),
                ),
              );
            } else {
              None;
            };
          })
        ->Js.Array.sortInPlaceWith(Fuzzy.sort, _)
        ->Array.map(item =>
            {
              TagsEditor.contents: item.contents,
              action: () => {
                let (volume, item) = item.contents;
                navigateTo(volume, item);
              },
            }
          )
        ->Array.slice(~offset=0, ~len=30);
      },
      [|nav|],
    );

  let (prev, next) =
    getSiblings(nav, volume, content)->Lets.Opt.or_((None, None));

  <div
    className=Css.(
      style([
        position(`relative),
        width(px(600)),
        alignSelf(`center),
        marginBottom(px(16)),
      ])
    )>
    <div
      className=Css.(
        style([
          textAlign(`center),
          flexDirection(`row),
          justifyContent(`center),
          alignItems(`center),
          fontSize(px(24)),
          fontWeight(`bold),
          padding(px(8)),
        ])
      )>
      {switch (prev) {
       | None => React.null
       | Some(prev) =>
         <button onClick={evt => navigateTo(volume, prev)}>
           {React.string("<")}
         </button>
       }}
      {React.string(content##title)}
      {switch (next) {
       | None => React.null
       | Some(next) =>
         <button onClick={evt => navigateTo(volume, next)}>
           {React.string(">")}
         </button>
       }}
    </div>
    <TagsEditor.Autocomplete
      getItems
      renderItem={((volume, item)) =>
        <div> {React.string(volume##title ++ " > " ++ item##title)} </div>
      }
      placeholder="Select a chapter / talk / item"
    />
  </div>;
  // {opened
  // ? <div className=Css.(style([
  //   position(`absolute),
  //       width(`percent(100.)),
  //   top(`percent(100.)),
  //   marginTop(px(8)),
  //   backgroundColor(white),
  //   boxShadow(~blur=px(5), hex("ccc")),
  //   borderRadius(px(3)),
  //   padding(px(8))
  // ]))>
  //   <input
  //     autoFocus={true}
  //     value=text
  //     className=Css.(style([
  //       // width(`percent(100.)),
  //       alignSelf(`stretch),
  //       padding(px(8)),
  //       fontSize(px(20))
  //     ]))
  //     onChange={evt => {
  //       update((true, evt->ReactEvent.Form.target##value))
  //     }}
  //     onBlur={evt => {
  //       update((false, text))
  //     }}
  //     placeholder="Select a chapter / talk / item"
  //   />
  // </div>
  // : React.null}
};