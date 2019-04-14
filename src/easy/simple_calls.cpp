/*  This file is part of mastodon-cpp.
 *  Copyright © 2018, 2019 tastytea <tastytea@tastytea.de>
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

using namespace Mastodon::Easy;

const return_entity<Status> API::send_toot(const Status &status)
{
    return send_post(status);
}

const return_entity<Status> API::send_post(const Status &status)
{
    parameters params;

    if (!status.content().empty())
    {
        params.push_back({ "status", { status.content() }});
    }
    else
    {
        ttdebug << "ERROR: Easy::Status::content can not be empty.\n";
        return { 22, "Easy::Status::content can not be empty", 0, Status() };
    }

    if (!status.in_reply_to_id().empty())
    {
        params.push_back({ "in_reply_to_id",
                           { status.in_reply_to_id() }});
    }
    if (status.sensitive())
    {
        params.push_back({ "sensitive", { "true" }});
    }
    if (!status.spoiler_text().empty())
    {
        params.push_back({ "spoiler_text", { status.spoiler_text() }});
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
        params.push_back({ "visibility", { visibility }});
    }
    if (!status.language().empty())
    {
        params.push_back({ "language", { status.language() }});
    }
    if (!status.media_attachments().empty())
    {
        std::vector<string> media_ids;
        for (const Attachment &att : status.media_attachments())
        {
            parameters param_att;
            if (!att.file().empty())
            {
                param_att.push_back({ "file", { att.file() }});
            }
            else
            {
                ttdebug << "ERROR: Easy::Attachment::file can not be empty.\n";
                return { 22, "Easy::Attachment::file can not be empty",
                         0, Status() };
            }
            if (!att.description().empty())
            {
                param_att.push_back({ "description", { att.description() }});
            }
            if (!att.focus().empty())
            {
                param_att.push_back({ "focus",
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
                         ret.http_error_code, Status(ret.answer) };
            }
        }

        params.push_back({ "media_ids", media_ids });
    }

    return_call ret = post(API::v1::statuses, params);
    return { ret.error_code, ret.error_message, ret.http_error_code,
             Status(ret.answer) };
}

const return_entity_vector<Notification> API::get_notifications(
    const uint16_t limit, const string since_id, const string max_id)
{
    parameters params;

    params.push_back({ "limit", { std::to_string(limit) } });
    if (!since_id.empty())
    {
        params.push_back({ "since_id", { since_id } });
    }
    if (!max_id.empty())
    {
        params.push_back({ "max_id", { max_id } });
    }

    return_call ret = API::get(API::v1::notifications, params);

    if (ret.error_code == 0)
    {
        const vector<string> &answer_v = json_array_to_vector(ret.answer);
        vector<Notification> notifications;
        notifications.resize(answer_v.size());

        // Transform vector of strings to vector of Notification.
        std::transform(answer_v.begin(), answer_v.end(), notifications.begin(),
                       [](const string &s)
                       { return Notification(s); });

        return { ret.error_code, ret.error_message, ret.http_error_code,
                 notifications };
    }
    else
    {
        ttdebug << "ERROR: Could not get notifications.\n";
        return { ret.error_code, ret.error_message, ret.http_error_code, {} };
    }
}
