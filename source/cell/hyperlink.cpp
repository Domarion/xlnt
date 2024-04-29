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

#include <xlnt/cell/hyperlink.hpp>
#include <xlnt/utils/exceptions.hpp>
#include <detail/implementations/hyperlink_impl.hpp>

namespace xlnt {

hyperlink::hyperlink(detail::hyperlink_impl *d)
    : d_(d)
{
}

relationship hyperlink::relationship() const
{
    return {};
//    if (!external())
//    {
//        throw xlnt::exception("only external hyperlinks have associated relationships");
//    }

//    return d_->relationship;
}

std::string hyperlink::url() const
{
    return {};
//    if (!external())
//    {
//        throw xlnt::exception("only external hyperlinks have associated urls");
//    }

//    return d_->relationship.target().to_string();
}

std::string hyperlink::target_range() const
{
    return {};

//    if (external())
//    {
//        throw xlnt::exception("only internal hyperlinks have a target range");
//    }

//    return d_->relationship.target().to_string();
}

bool hyperlink::external() const
{
    return false;
//    return d_->relationship.target_mode() == target_mode::external;
}

bool hyperlink::has_display() const
{
    return d_->display.has_value();
}

void hyperlink::display(const std::string &value)
{
    d_->display.emplace(value);
}

const std::string &hyperlink::display() const
{
    return d_->display.value();
}

bool hyperlink::has_tooltip() const
{
    return d_->tooltip.has_value();
}

void hyperlink::tooltip(const std::string &value)
{
    d_->tooltip.emplace(value);
}

const std::string &hyperlink::tooltip() const
{
    return d_->tooltip.value();
}

bool hyperlink::has_location() const
{
    return d_->location.has_value();
}

void hyperlink::location(const std::string &value)
{
    d_->location.emplace(value);
}

const std::string &hyperlink::location() const
{
    return d_->location.value();
}

} // namespace xlnt
