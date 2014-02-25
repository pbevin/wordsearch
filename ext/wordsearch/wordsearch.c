#include <ruby.h>

extern int an_main(const char *pattern, const char *dictfile, void(*)(const char *word));
extern int fw_main(const char *pattern, const char *dictfile, int cryptogram, void(*)(const char *word));

void wsYield(const char *word) {
  rb_yield(rb_str_new2(word));
}

const char *dictfile(VALUE self) {
  VALUE dict = rb_iv_get(self, "@dict");
  return StringValueCStr(dict);
}

VALUE an(VALUE self, VALUE pattern) {
  const char *pat = StringValueCStr(pattern);
  an_main(pat, dictfile(self), wsYield);
  return Qnil;
}

VALUE fw(VALUE self, VALUE pattern) {
  const char *pat = StringValueCStr(pattern);
  fw_main(pat, dictfile(self), 0, wsYield);
  return Qnil;
}

VALUE cr(VALUE self, VALUE pattern) {
  const char *pat = StringValueCStr(pattern);
  fw_main(pat, dictfile(self), 1, wsYield);
  return Qnil;
}

void Init_wordsearch() {
  VALUE wordsearch = rb_define_class("Wordsearch", rb_cObject);
  rb_define_method(wordsearch, "an", an, 1);
  rb_define_method(wordsearch, "fw", fw, 1);
  rb_define_method(wordsearch, "cr", cr, 1);
}
