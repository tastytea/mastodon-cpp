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

#include <algorithm>
#include "easy.hpp"
#include "debug.hpp"
#include "easy/entities/status.hpp"
#include "easy/entities/attachment.hpp"
#include "easy/entities/notification.hpp"

using namespace Mastodon;

const return_entity Easy::send_toot(const Status &status)
{
    return send_post(status);
}

const return_entity Easy::send_post(const Status &status)
{
    API::parametermap parameters;

    if (!status.content().empty())
    {
        parameters.insert({ "status", { status.content() }});
    }
    else
    {
        ttdebug << "ERROR: Easy::Status::content can not be empty.\n";
        return {22, "Easy::Status::content can not be empty", GenericEntity()};
    }

    if (!status.in_reply_to_id().empty())
    {
        parameters.insert({ "in_reply_to_id",
                          { status.in_reply_to_id() }});
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
                return { 22, "Easy::Attachment::file can not be empty",
                    GenericEntity() };
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

            return_call ret = post(API::v1::media, param_att);
            if (ret.error_code == 0)
            {
                Attachment attachment(ret.answer);
                media_ids.push_back(attachment.id());
            }
            else
            {
                ttdebug << "ERROR: Could not upload file.\n";
                return { ret.error_code, ret.error_message,
                    GenericEntity(ret.answer) };
            }
        }

        parameters.insert({ "media_ids", media_ids });
    }

    return_call ret = post(API::v1::statuses, parameters);
    return { ret.error_code, ret.error_message, GenericEntity(ret.answer) };
}

const return_entity_vector Easy::get_notifications(const uint16_t limit,
                                                   const string since_id,
                                                   const string max_id)
{
    API::parametermap parameters;

    parameters.insert({ "limit", { std::to_string(limit) } });
    if (!since_id.empty())
    {
        parameters.insert({ "since_id", { since_id } });
    }
    if (!max_id.empty())
    {
        parameters.insert({ "max_id", { max_id } });
    }

    return_call ret = API::get(API::v1::notifications, parameters);

    if (ret.error_code == 0)
    {
        const vector<string> &answer_v = json_array_to_vector(ret.answer);
        vector<GenericEntity> notifications;
        notifications.resize(answer_v.size());

        // Transform vector of strings to vector of Notification.
        std::transform(answer_v.begin(), answer_v.end(), notifications.begin(),
                       [](const string s)
                       { return GenericEntity(s); });

        return { ret.error_code, ret.error_message, notifications };
    }
    else
    {
        ttdebug << "ERROR: Could not get notifications.\n";
        return { ret.error_code, ret.error_message, {} };
    }
}
