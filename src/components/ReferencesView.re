[@react.component]
let make =
    (~containerRef, ~positionedAnnotations, ~state: Types.state, ~dispatch) => {
  <div
    ref={ReactDOMRe.Ref.domRef(containerRef)}
    className=Css.(
      style([
        minWidth(px(50)),
        marginLeft(px(10)),
        marginRight(px(20)),
        flexDirection(`row),
        position(`relative),
      ])
    )>
    {positionedAnnotations
     ->Array.mapWithIndex((i, (ann: Types.Annotation.t, references)) => {
         let tags =
           ann.tags->List.keepMap(tid => state.tags->Map.String.get(tid));
         let tagColors = tags->List.map(tag => tag.color);
         let styleColor = color =>
           ReactDOMRe.Style.make(~backgroundColor=color, ());
         let tagColor =
           switch (tagColors) {
           | [color, ..._] => color
           | [] => "#ccc"
           };
         <div
           onClick={evt => dispatch(`Select(ann.id))}
           key={string_of_int(i)}
           className=Css.(
             style([
               width(px(10)),
               //  marginLeft(px(2)),
               cursor(`pointer),
               hover([
                 selector(
                   " > div > div",
                   [outline(px(1), `solid, Colors.outline)],
                 ),
               ]),
             ])
           )>
           {references
            ->Array.mapWithIndex((i, (top, height, ref: Types.reference)) =>
                <div
                  key={Js.Int.toString(i)}
                  onClick={evt =>
                    Web.Selection.current()
                    ->Web.Selection.fromIdOffset(ref.start, ref.stop)
                  }
                  className=Css.(
                    style([
                      // backgroundColor(rgba(255, 0, 0, 0.3)),
                      width(px(4)),
                      borderLeft(px(3), `solid, Colors.background),
                      borderRight(px(3), `solid, Colors.background),
                      position(`absolute),
                    ])
                  )
                  style={ReactDOMRe.Style.make(
                    ~top=Js.Float.toString(top) ++ "px",
                    // ~marginLeft=Js.Int.toString(i * 5) ++ "px",
                    ~height=Js.Float.toString(height) ++ "px",
                    // ~backgroundColor=tagColor,
                    (),
                  )}>
                  <div
                    className=Css.(
                      ann.id == state.current.id
                        ? style([outline(px(1), solid, Colors.outline)])
                        : ""
                    )
                    style={ReactDOMRe.Style.make(
                      ~backgroundColor=tagColor,
                      ~height=Js.Float.toString(height) ++ "px",
                      ~width="4px",
                      (),
                    )}
                  />
                </div>
              )
            ->React.array}
         </div>;
       })
     ->React.array}
  </div>;
};