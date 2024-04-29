#pragma once

#include <cstddef>
#include <string>

#include <xlnt/utils/optional.hpp>

namespace xlnt {

class alignment;
class border;
class fill;
class font;
class number_format;
class protection;

namespace detail {

struct stylesheet;

struct style_impl
{
	stylesheet *parent;

    bool operator==(const style_impl& rhs) const
    {
        return name == rhs.name
            && formatting_record_id == rhs.formatting_record_id
            && custom_builtin == rhs.custom_builtin
            && hidden_style == rhs.hidden_style
            && builtin_id == rhs.builtin_id
            && outline_style == rhs.outline_style
            && alignment_id == rhs.alignment_id
            && alignment_applied == rhs.alignment_applied
            && border_id == rhs.border_id
            && border_applied == rhs.border_applied
            && fill_id == rhs.fill_id
            && fill_applied == rhs.fill_applied
            && font_id == rhs.font_id
            && font_applied == rhs.font_applied
            && number_format_id == rhs.number_format_id
            && number_format_applied == number_format_applied
            && protection_id == rhs.protection_id
            && protection_applied == rhs.protection_applied
            && pivot_button_ == rhs.pivot_button_
            && quote_prefix_ == rhs.quote_prefix_;
    }

	std::string name;
	std::size_t formatting_record_id;

	bool custom_builtin;
	bool hidden_style;

    std::optional<std::size_t> builtin_id;
    std::optional<std::size_t> outline_style;

    std::optional<std::size_t> alignment_id;
    std::optional<bool> alignment_applied;

    std::optional<std::size_t> border_id;
    std::optional<bool> border_applied;

    std::optional<std::size_t> fill_id;
    std::optional<bool> fill_applied;

    std::optional<std::size_t> font_id;
    std::optional<bool> font_applied;

    std::optional<std::size_t> number_format_id;
    std::optional<bool> number_format_applied;

    std::optional<std::size_t> protection_id;
    std::optional<bool> protection_applied;

    bool pivot_button_ = false;
    bool quote_prefix_ = false;
};

} // namespace detail
} // namespace xlnt
