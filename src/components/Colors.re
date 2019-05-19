open Css;
module Light = {
  let background = hex("eee");
  let text = hex("333");
  let hover = hex("ddd");
  let outline = black;
};

module Dark = {
  let background = hex("333");
  let text = hex("ddd");
  let hover = hex("444");
  let outline = white;
};

// include Light;
include Dark;