#include "ruby.h"
#include "bktree.h"
#include "levenshtein.h"

VALUE cBkTree;

static VALUE rb_bktree_alloc(VALUE klass) {
    VALUE obj;
    obj = Data_Wrap_Struct(klass, 0, bktree_destroy, bktree_new(levenshtein_distance));
    return obj;
}

static VALUE rb_bktree_add(VALUE self, VALUE word) {
    StringValue(word);

    BKTree * bktree;
    Data_Get_Struct(self, BKTree, bktree);

    bktree_add(bktree, RSTRING_PTR(word), RSTRING_LEN(word));

    return Qnil;
}

static VALUE rb_bktree_query(VALUE self, VALUE word, VALUE max) {
    StringValue(word);

    BKTree * bktree;
    Data_Get_Struct(self, BKTree, bktree);

    VALUE result_out = rb_ary_new();
    BKResult * result = bktree_query(bktree, RSTRING_PTR(word), RSTRING_LEN(word), FIX2INT(max));
    while(result) {
        VALUE result_node = rb_ary_new();

        rb_ary_push(result_node, rb_str_new(BKTREE_GET_STRING(bktree, result->string_offset), BKTREE_GET_STRING_LEN(bktree, result->string_offset)));
        rb_ary_push(result_node, INT2FIX(result->distance));

        rb_ary_push(result_out, result_node);
        result = result->next;
    }

    return result_out;
}

void Init_bktree() {
    cBkTree = rb_define_class("BkTree", rb_cObject);
    rb_define_alloc_func(cBkTree, rb_bktree_alloc);
    rb_define_method(cBkTree, "add", rb_bktree_add, 1);
    rb_define_method(cBkTree, "query", rb_bktree_query, 2);
}
