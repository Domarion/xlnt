// Copyright (c) 2014-2021 Thomas Fussell
// Copyright (c) 2010-2015 openpyxl
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE
//
// @license: http://www.opensource.org/licenses/mit-license.php
// @author: see AUTHORS file

#include <xlnt/styles/alignment.hpp>
#include <xlnt/styles/border.hpp>
#include <xlnt/styles/fill.hpp>
#include <xlnt/styles/font.hpp>
#include <xlnt/styles/number_format.hpp>
#include <xlnt/styles/protection.hpp>
#include <xlnt/styles/style.hpp>
#include <detail/implementations/style_impl.hpp>
#include <detail/implementations/stylesheet.hpp>

namespace {

std::vector<xlnt::number_format>::iterator find_number_format(
    std::vector<xlnt::number_format> &number_formats, std::size_t id)
{
    return std::find_if(number_formats.begin(), number_formats.end(),
        [=](const xlnt::number_format &nf) { return nf.id() == id; });
}

} // namespace

namespace xlnt {

style::style(detail::style_impl *d)
    : d_(d)
{
}

bool style::hidden() const
{
    return d_->hidden_style;
}

style style::hidden(bool value)
{
    d_->hidden_style = value;
    return style(d_);
}

std::size_t style::builtin_id() const
{
    return d_->builtin_id.value();
}

bool style::builtin() const
{
    return d_->builtin_id.has_value();
}

std::string style::name() const
{
    return d_->name;
}

style style::name(const std::string &name)
{
    d_->name = name;
    return *this;
}

bool style::custom_builtin() const
{
    return d_->builtin_id.has_value() && d_->custom_builtin;
}

bool style::operator==(const style &other) const
{
    return name() == other.name();
}

bool style::operator!=(const style &other) const
{
    return !operator==(other);
}

xlnt::alignment style::alignment() const
{
    return d_->parent->alignments.at(d_->alignment_id.value());
}

style style::alignment(const xlnt::alignment &new_alignment, std::optional<bool> applied)
{
    d_->alignment_id = d_->parent->find_or_add(d_->parent->alignments, new_alignment);
    d_->alignment_applied = applied;

    return *this;
}

xlnt::border style::border() const
{
    return d_->parent->borders.at(d_->border_id.value());
}

style style::border(const xlnt::border &new_border, std::optional<bool> applied)
{
    d_->border_id = d_->parent->find_or_add(d_->parent->borders, new_border);
    d_->border_applied = applied;

    return *this;
}

xlnt::fill style::fill() const
{
    return d_->parent->fills.at(d_->fill_id.value());
}

style style::fill(const xlnt::fill &new_fill, std::optional<bool> applied)
{
    d_->fill_id = d_->parent->find_or_add(d_->parent->fills, new_fill);
    d_->fill_applied = applied;

    return *this;
}

xlnt::font style::font() const
{
    return d_->parent->fonts.at(d_->font_id.value());
}

style style::font(const xlnt::font &new_font, std::optional<bool> applied)
{
    d_->font_id = d_->parent->find_or_add(d_->parent->fonts, new_font);
    d_->font_applied = applied;

    return *this;
}

xlnt::number_format style::number_format() const
{
    auto match = find_number_format(d_->parent->number_formats,
        d_->number_format_id.value());

    if (match == d_->parent->number_formats.end())
    {
        throw invalid_attribute();
    }

    return *match;
}

style style::number_format(const xlnt::number_format &new_number_format, std::optional<bool> applied)
{
    auto copy = new_number_format;

    if (!copy.has_id())
    {
        copy.id(d_->parent->next_custom_number_format_id());
        d_->parent->number_formats.push_back(copy);
    }
    else if (find_number_format(d_->parent->number_formats, copy.id())
        == d_->parent->number_formats.end())
    {
        d_->parent->number_formats.push_back(copy);
    }

    d_->number_format_id = copy.id();
    d_->number_format_applied = applied;

    return *this;
}

xlnt::protection style::protection() const
{
    return d_->parent->protections.at(d_->protection_id.value());
}

style style::protection(const xlnt::protection &new_protection, std::optional<bool> applied)
{
    d_->protection_id = d_->parent->find_or_add(d_->parent->protections, new_protection);
    d_->protection_applied = applied;

    return *this;
}

bool style::alignment_applied() const
{
    return d_->alignment_applied.has_value()
        ? d_->alignment_applied.value()
        : d_->alignment_id.has_value();
}

bool style::border_applied() const
{
    return d_->border_applied.has_value()
        ? d_->border_applied.value()
        : d_->border_id.has_value();
}

bool style::fill_applied() const
{
    return d_->fill_applied.has_value()
        ? d_->fill_applied.value()
        : d_->fill_id.has_value();
}

bool style::font_applied() const
{
    return d_->font_applied.has_value()
        ? d_->font_applied.value()
        : d_->font_id.has_value();
}

bool style::number_format_applied() const
{
    return d_->number_format_applied.has_value()
        ? d_->number_format_applied.value()
        : d_->number_format_id.has_value();
}

bool style::protection_applied() const
{
    return d_->protection_applied.has_value()
        ? d_->protection_applied.value()
        : d_->protection_id.has_value();
}

bool style::pivot_button() const
{
    return d_->pivot_button_;
}

void style::pivot_button(bool show)
{
    d_->pivot_button_ = show;
}

bool style::quote_prefix() const
{
    return d_->quote_prefix_;
}

void style::quote_prefix(bool quote)
{
    d_->quote_prefix_ = quote;
}

} // namespace xlnt
