/*  This file is part of mastodon-cpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "return_types_easy.hpp"
#include "easy/entities/account.hpp"
#include "easy/entities/application.hpp"
#include "easy/entities/attachment.hpp"
#include "easy/entities/card.hpp"
#include "easy/entities/context.hpp"
#include "easy/entities/emoji.hpp"
#include "easy/entities/instance.hpp"
#include "easy/entities/list.hpp"
#include "easy/entities/mention.hpp"
#include "easy/entities/notification.hpp"
#include "easy/entities/relationship.hpp"
#include "easy/entities/report.hpp"
#include "easy/entities/results.hpp"
#include "easy/entities/status.hpp"
#include "easy/entities/tag.hpp"
#include "easy/entities/token.hpp"
#include "easy/entities/pushsubscription.hpp"
#include "easy/entities/filter.hpp"
#include "easy/entities/poll.hpp"
#include "easy/entities/conversation.hpp"

using namespace Mastodon;

template<typename T>
Easy::return_entity<T>::return_entity()
    : entity()
{}

template<typename T>
Easy::return_entity<T>::return_entity(const uint8_t ec, const string &em,
                                      const uint16_t hec, const T &ent)
    : entity(ent)
{
    error_code = ec;
    error_message = em;
    http_error_code = hec;
}

template<typename T>
Easy::return_entity<T>::return_entity(const error ec, const string &em,
                                      const uint16_t hec, const T &ent)
    : entity(ent)
{
    error_code = static_cast<uint8_t>(ec);
    error_message = em;
    http_error_code = hec;
}

template<typename T>
Easy::return_entity<T>::return_entity::operator const T() const
{
    return entity;
}

template<typename T>
Easy::return_entity<T>::return_entity::operator const string() const
{
    return entity.to_string();
}

// Explicit instantiations, so it can be used from outside.
template struct Easy::return_entity<Easy::Account>;
template struct Easy::return_entity<Easy::Application>;
template struct Easy::return_entity<Easy::Attachment>;
template struct Easy::return_entity<Easy::Card>;
template struct Easy::return_entity<Easy::Context>;
template struct Easy::return_entity<Easy::Emoji>;
template struct Easy::return_entity<Easy::Instance>;
template struct Easy::return_entity<Easy::List>;
template struct Easy::return_entity<Easy::Mention>;
template struct Easy::return_entity<Easy::Notification>;
template struct Easy::return_entity<Easy::Relationship>;
template struct Easy::return_entity<Easy::Report>;
template struct Easy::return_entity<Easy::Results>;
template struct Easy::return_entity<Easy::Status>;
template struct Easy::return_entity<Easy::Tag>;
template struct Easy::return_entity<Easy::Token>;
template struct Easy::return_entity<Easy::PushSubscription>;
template struct Easy::return_entity<Easy::Filter>;
template struct Easy::return_entity<Easy::Poll>;
template struct Easy::return_entity<Easy::Conversation>;


template<typename T>
Easy::return_entity_vector<T>::
return_entity_vector::return_entity_vector()
    : entities()
{}

template<typename T>
Easy::return_entity_vector<T>::return_entity_vector::return_entity_vector(
    const uint8_t ec, const string &em,
    const uint16_t hec, const vector<T> &vec)
    : entities(vec)
{
    error_code = ec;
    error_message = em;
    http_error_code = hec;
}

template<typename T>
Easy::return_entity_vector<T>::return_entity_vector::operator const vector<T>()
    const
{
    return entities;
}

// Explicit instantiations, so it can be used from outside.
template struct Easy::return_entity_vector<Easy::Account>;
template struct Easy::return_entity_vector<Easy::Application>;
template struct Easy::return_entity_vector<Easy::Attachment>;
template struct Easy::return_entity_vector<Easy::Card>;
template struct Easy::return_entity_vector<Easy::Context>;
template struct Easy::return_entity_vector<Easy::Emoji>;
template struct Easy::return_entity_vector<Easy::Instance>;
template struct Easy::return_entity_vector<Easy::List>;
template struct Easy::return_entity_vector<Easy::Mention>;
template struct Easy::return_entity_vector<Easy::Notification>;
template struct Easy::return_entity_vector<Easy::Relationship>;
template struct Easy::return_entity_vector<Easy::Report>;
template struct Easy::return_entity_vector<Easy::Results>;
template struct Easy::return_entity_vector<Easy::Status>;
template struct Easy::return_entity_vector<Easy::Tag>;
template struct Easy::return_entity_vector<Easy::Token>;
template struct Easy::return_entity_vector<Easy::PushSubscription>;
template struct Easy::return_entity_vector<Easy::Filter>;
