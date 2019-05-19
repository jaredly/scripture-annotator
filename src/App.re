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
  let make =
      (
        ~fn,
        ~loaded,
        ~loading=() =>
                   <div
                     className=Css.(
                       style([
                         textAlign(`center),
                         alignSelf(`stretch),
                         padding(px(50)),
                         flex(1),
                       ])
                     )>
                     {React.string("Loading...")}
                   </div>,
      ) => {
    let value = Hooks.useLoading(fn);
    switch (value) {
    | None => loading()
    | Some(value) => loaded(value)
    };
  };
};

module PageWrapper = {
  [@react.component]
  let make = (~content, ~volume, ~nav) => {
    let (state, dispatch) = React.useReducer(Page.reduce, Types.empty);

    let (data, setData) = Hooks.useState(None);

    React.useEffect0(() => {
      {
        let%Lets.Async.Consume state = Database.load();
        dispatch(`Reset(state));
      };
      None;
    });

    React.useEffect2(
      () => {
        {
          let%Lets.Async.Consume data =
            Content.content(volume##item_id, content##subitem_id);
          setData(Some(data));
        };
        None;
      },
      (volume##item_id, content##subitem_id),
    );

    <div
      className=Css.(
        style([
          position(`absolute),
          backgroundColor(Colors.background),
          color(Colors.text),
          selector(
            "textarea",
            [backgroundColor(Colors.background), color(Colors.text)],
          ),
          selector(
            "input",
            [backgroundColor(Colors.background), color(Colors.text)],
          ),
          selector(
            "button",
            [backgroundColor(Colors.background), color(Colors.text)],
          ),
          top(`zero),
          right(`zero),
          left(`zero),
          bottom(`zero),
        ])
      )>
      <TopNav nav volume content />
      // {React.string(content##title)}
      {switch (data) {
       | None =>
         <div
           className=Css.(
             style([
               textAlign(`center),
               alignSelf(`stretch),
               padding(px(50)),
               flex(1),
             ])
           )>
           {React.string("Loading...")}
         </div>
       | Some(data) =>
         <Page meta=content volume content=data state dispatch />
       }}
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