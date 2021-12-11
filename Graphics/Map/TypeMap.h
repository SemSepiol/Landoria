#ifndef TYPEMAP_H
#define TYPEMAP_H

struct TypeMap
{
  enum Overlay {
    NoOverlay,
    Political,
    HighlightResources
  };

  enum TypeContent{
    All,
    Nothing,
    Units,
    Resources,
    Building,
  };

  Overlay overplay = NoOverlay;
  TypeContent type_content = All;
  bool show_notvisible = true;
  bool show_other_landscapes = true;
};

#endif // TYPEMAP_H
