/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef PAGESPEED_KERNEL_HTML_HTML_WRITER_FILTER_H_
#define PAGESPEED_KERNEL_HTML_HTML_WRITER_FILTER_H_

#include "pagespeed/kernel/base/basictypes.h"
#include "pagespeed/kernel/base/string.h"
#include "pagespeed/kernel/base/string_util.h"
#include "pagespeed/kernel/html/html_element.h"
#include "pagespeed/kernel/html/html_filter.h"
#include "pagespeed/kernel/html/html_name.h"
#include "pagespeed/kernel/html/html_node.h"

namespace net_instaweb {

class HtmlParse;
class Writer;

// Filter that serializes HTML to a Writer stream.
class HtmlWriterFilter : public HtmlFilter {
 public:
  explicit HtmlWriterFilter(HtmlParse* html_parse);

  void set_writer(Writer* writer) { writer_ = writer; }
  ~HtmlWriterFilter() override;

  void StartDocument() override;
  void EndDocument() override;
  void StartElement(HtmlElement* element) override;
  void EndElement(HtmlElement* element) override;
  void Cdata(HtmlCdataNode* cdata) override;
  void Comment(HtmlCommentNode* comment) override;
  void IEDirective(HtmlIEDirectiveNode* directive) override;
  void Characters(HtmlCharactersNode* characters) override;
  void Directive(HtmlDirectiveNode* directive) override;
  void Flush() override;
  void DetermineEnabled(GoogleString* disabled_reason) override;
  // This filter will not change urls.
  bool CanModifyUrls() override { return false; }
  ScriptUsage GetScriptUsage() const override { return kNeverInjectsScripts; }

  void set_max_column(int max_column) { max_column_ = max_column; }
  void set_case_fold(bool case_fold) { case_fold_ = case_fold; }

  const char* Name() const override { return "HtmlWriter"; }

 protected:
  // Clear various variables for rewriting a new html file.
  virtual void Clear();

  Writer* writer() { return writer_; }

  // Terminates the current lazy close element if it is not already terminated.
  void TerminateLazyCloseElement();

 private:
  void EmitBytes(const StringPiece& str);

  // Emits an HTML name, possibly case-folded depending on the
  // caller-specified option.
  void EmitName(const HtmlName& name);

  HtmlElement::Style GetElementStyle(HtmlElement* element);

  // Escapes arbitrary text as HTML, e.g. turning & into &amp;.  If quoteChar
  // is non-zero, e.g. '"', then it would escape " as well.
  void EncodeBytes(const GoogleString& val, int quoteChar);

  HtmlParse* html_parse_;
  Writer* writer_;

  // Helps writer exploit shortcuts like <img .../> rather than writing
  // <img ...></img>.  At the end of StartElement, we defer writing the ">"
  // until we see what's coming next.  If it's the matching end_tag, then
  // we can emit />.  If something else comes first, then we have to
  // first emit the delayed ">" before continuing.
  HtmlElement* lazy_close_element_;

  int column_;
  int max_column_;
  int write_errors_;
  bool case_fold_;
  GoogleString case_fold_buffer_;

  DISALLOW_COPY_AND_ASSIGN(HtmlWriterFilter);
};

}  // namespace net_instaweb

#endif  // PAGESPEED_KERNEL_HTML_HTML_WRITER_FILTER_H_
