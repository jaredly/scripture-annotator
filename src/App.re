
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
      <div className=Css.(style([
        fontSize(px(20)),
        marginBottom(px(16))
      ]))>
        {React.string("Feast upon the word")}
      </div>
      {
        nav->Js.Dict.values->Array.map(item => (
          <div key={item##uri} onClick={(_) => {
            Web.Location.setHash("#" ++ item##uri)
          }}>
            {React.string(item##title)}
          </div>
        ))->React.array
      }
    </div>
  };
};

let byUri = (nav, uri) => {
  nav->Js.Dict.values->Array.getBy(item => item##uri == uri)
};

let getSubitem = (navs, uri) => {
  navs->Array.getBy(item => item##uri == uri)
};

module Volume = {
  [@react.component]
  let make = (~volume) => {
    <div>
      {React.string("Volume")}
      {volume##nav->Array.map(nav => (
        <div onClick={evt => {
          Web.Location.setHash(volume##uri ++ ":" ++ nav##uri)
        }}>
          {React.string(nav##title)}
        </div>
      ))->React.array}
    </div>
  }
};

module Loading = {
  [@react.component]
  let make = (~value, ~loaded, ~loading=() => React.string("Loading....")) => {
    switch value {
      | None => loading()
      | Some(value) => loaded(value)
    }
  };
}

module Page = {
  [@react.component]
  let make = (~content, ~volume) => {
    let data = Hooks.useLoading(() => Content.content(volume##item_id, content##subitem_id));
    // Js.log(data);
    <div>
      {React.string("Content: " ++ content##title)}
      <Loading
        value=data
        loaded={data => {
          <div>
            <div dangerouslySetInnerHTML={{"__html": data##content}} />
          </div>
        }}
      />
    </div>
  }
};

module App = {
  [@react.component]
  let make = () => {
    let hash = Hooks.useHash();
    let nav = Hooks.useLoading(() => Content.nav);
    <Loading
      value=nav
      loaded={nav => {
        let parts = hash == "" ? None : Some(hash->Js.String.sliceToEnd(~from=1) |> Js.String.split(":"));
        // Js.log(parts)
        let path = {
          let%Lets.Opt parts = parts;
          switch parts {
            | [|first|] =>
              let%Lets.Opt vol = nav->byUri(first)
              Some(`Volume(vol))
            | [|first, second|] =>
              let%Lets.Opt vol = nav->byUri(first)
              switch (vol##nav->getSubitem(second)) {
                | None => Some(`Volume(vol))
                | Some(content) => Some(`Content(vol, content))
              }
            | _ => None
          };
        };

        switch path {
          | None
          | Some(`Home) =>
          <Home nav />
          | Some(`Volume(volume)) =>
            <Volume volume />
          | Some(`Content(volume, content)) =>
            <Page content volume />
        }
      }}
    />
  }
};

ReactDOMRe.renderToElementWithId(<App />, "root")
