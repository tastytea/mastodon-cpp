/*  This file is part of mastodon-cpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "easy.hpp"
#include "macros.hpp"
#include "easy/entities/status.hpp"
#include "easy/entities/attachment.hpp"

using namespace Mastodon;

const Easy::Status Easy::send_toot(const Status &status, uint_fast16_t &error)
{
    return send_post(status, error);
}

const Easy::Status Easy::send_post(const Status &status, uint_fast16_t &error)
{
    API::parametermap parameters;
    string answer;
    error = 0;

    if (!status.content().empty())
    {
        parameters.insert({ "status", { status.content() }});
    }
    else
    {
        ttdebug << "ERROR: Easy::Status::content can not be empty.\n";
        error = 11;
        return Status();
    }

    if (status.in_reply_to_id() != 0)
    {
        parameters.insert({ "in_reply_to_id",
                          { std::to_string(status.in_reply_to_id()) }});
    }
    if (status.sensitive())
    {
        parameters.insert({ "sensitive", { "true" }});
    }
    if (!status.spoiler_text().empty())
    {
        parameters.insert({ "spoiler_text", { status.spoiler_text() }});
    }
    if (status.visibility() != visibility_type::Undefined)
    {
        string visibility;
        switch (status.visibility())
        {
            case visibility_type::Direct:
                visibility = "direct";
                break;
            case visibility_type::Private:
                visibility = "private";
                break;
            case visibility_type::Unlisted:
                visibility = "unlisted";
                break;
            case visibility_type::Public:
                visibility = "public";
                break;
            default:
                break;
        };
        parameters.insert({ "visibility", { visibility }});
    }
    if (!status.language().empty())
    {
        parameters.insert({ "language", { status.language() }});
    }
    if (!status.media_attachments().empty())
    {
        std::vector<string> media_ids;
        for (const Attachment &att : status.media_attachments())
        {
            API::parametermap param_att;
            if (!att.file().empty())
            {
                param_att.insert({ "file", { att.file() }});
            }
            else
            {
                ttdebug << "ERROR: Easy::Attachment::file can not be empty.\n";
                error = 11;
                return Status();
            }
            if (!att.description().empty())
            {
                param_att.insert({ "description", { att.description() }});
            }
            if (!att.focus().empty())
            {
                param_att.insert({ "focus",
                                 { std::to_string(att.focus()[0]) + ',' +
                                   std::to_string(att.focus()[1]) }});
            }

            error = post(API::v1::media, param_att, answer);
            if (error == 0)
            {
                Attachment attachment(answer);
                media_ids.push_back(std::to_string(attachment.id()));
            }
            else
            {
                ttdebug << "ERROR: Could not upload file.\n";
                return Status();
            }
        }

        parameters.insert({ "media_ids", media_ids });
    }

    error = post(API::v1::statuses, parameters, answer);
    if (error == 0)
    {
        return Status(answer);
    }
    else
    {
        return Status();
    }
}
