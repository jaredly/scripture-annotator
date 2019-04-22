type nav =
  Js.Dict.t({
    .
    "categoryID": string,
    "categoryName": string,
    "englishLanguageName": string,
    "imageRenditions": string,
    "iso639_3": string,
    "itemPackageVersion": string,
    "item_external_id": string,
    "item_id": string,
    "languageID": string,
    "nav":
      array
        // "collation_title": null
        // "end_date": null
        ({
          .
          "id": int,
          "image_renditions": option(string),
          "nav_section_id": int,
          "position": int,
          // "preview": null
          "primary_title": string,
          "short_title": option(string),
          "start_date": option(string),
          "subitem_id": string,
          "subtitle": option(string),
          "title": string,
          "title_number": option(int),
          "uri": string,
        }),
    "schemaVersion": string,
    "title": string,
    "uri": string,
  });

let nav: Js.Promise.t(nav) = {
  let%Lets.Async response = Web.fetch("/data/meta.json", Js.Obj.empty());
  response->Web.json;
};