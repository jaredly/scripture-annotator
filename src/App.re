// module Loading = {
//   let let_ = (value, fn) => {
//     switch value {
//       | None => <div>{React.string("Loading...")}</div>
//       | Some(v) => fn(v)
//     }
//   }
// }

module Home = {
  [@react.component]
  let make = (~nav) => {
    <div>
      <div
        className=Css.(style([fontSize(px(20)), marginBottom(px(16))]))>
        {React.string("Feast upon the word")}
      </div>
      {nav
       ->Js.Dict.values
       ->Array.map(item =>
           <div
             key={item##uri}
             onClick={_ => Web.Location.setHash("#" ++ item##uri)}>
             {React.string(item##title)}
           </div>
         )
       ->React.array}
    </div>;
  };
};

let byUri = (nav, uri) => {
  nav->Js.Dict.values->Array.getBy(item => item##uri == uri);
};

let getSubitem = (navs, uri) => {
  navs->Array.getBy(item => item##uri == uri);
};

let navigateTo = (volume, item) =>
  Web.Location.setHash(volume##uri ++ ":" ++ item##uri);

module Volume = {
  [@react.component]
  let make = (~volume) => {
    <div>
      {React.string("Volume")}
      {volume##nav
       ->Array.map(nav =>
           <div
             onClick={evt =>
               Web.Location.setHash(volume##uri ++ ":" ++ nav##uri)
             }>
             {React.string(nav##title)}
           </div>
         )
       ->React.array}
    </div>;
  };
};

module Loading = {
  [@react.component]
  let make = (~fn, ~loaded, ~loading=() => React.string("Loading....")) => {
    let value = Hooks.useLoading(fn);
    switch (value) {
    | None => loading()
    | Some(value) => loaded(value)
    };
  };
};

let getSiblings = (nav, volume, content) => {
  let%Lets.Opt nav = nav->Js.Dict.get(volume##item_id);
  let%Lets.Opt index =
    nav##nav
    ->Array.getIndexBy(item => item##subitem_id == content##subitem_id);
  Some((nav##nav[index - 1], nav##nav[index + 1]));
};

module TopNav = {
  [@react.component]
  let make = (~nav, ~volume, ~content) => {
    let getItems =
      React.useCallback1(
        text => {
          let allItems =
            nav
            ->Js.Dict.values
            ->Array.map(volume =>
                volume##nav->Array.map(nav => (volume, nav))
              )
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
};

module PageWrapper = {
  [@react.component]
  let make = (~content, ~volume, ~nav) => {
    let database = React.useMemo0(() => Database.load());
    let contentPromise =
      React.useMemo2(
        () => Content.content(volume##item_id, content##subitem_id),
        (volume##item_id, content##subitem_id),
      );
    let loader =
      React.useMemo2(
        ((), ()) => Js.Promise.all2((contentPromise, database)),
        (database, contentPromise),
      );
    <div>
      <TopNav nav volume content />
      // {React.string(content##title)}
      <Loading
        fn=loader
        loaded={((data, state)) =>
          <Page meta=content volume content=data state />
        }
      />
    </div>;
  };
};

module App = {
  let loader = () => Content.nav;
  [@react.component]
  let make = () => {
    let hash = Hooks.useHash();
    <Loading
      fn=loader
      loaded={nav => {
        let parts =
          hash == ""
            ? None
            : Some(
                hash->Js.String.sliceToEnd(~from=1) |> Js.String.split(":"),
              );
        // Js.log(parts)
        let path = {
          let%Lets.Opt parts = parts;
          switch (parts) {
          | [|first|] =>
            let%Lets.Opt vol = nav->byUri(first);
            Some(`Volume(vol));
          | [|first, second|] =>
            let%Lets.Opt vol = nav->byUri(first);
            switch (vol##nav->getSubitem(second)) {
            | None => Some(`Volume(vol))
            | Some(content) => Some(`Content((vol, content)))
            };
          | _ => None
          };
        };

        switch (path) {
        | None
        | Some(`Home) => <Home nav />
        | Some(`Volume(volume)) => <Volume volume />
        | Some(`Content(volume, content)) =>
          <PageWrapper content volume nav />
        };
      }}
    />;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");