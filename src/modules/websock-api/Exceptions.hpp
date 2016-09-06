/*
    Copyright (C) 2014-2016 Islog

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "core/auth/AuthFwd.hpp"
#include "exception/leosacexception.hpp"

namespace Leosac
{
namespace Module
{
namespace WebSockAPI
{

class MalformedMessage : public LEOSACException
{
  public:
    MalformedMessage(const std::string &detail = "");
    ;

  private:
    std::string build_msg(const std::string &detail) const;
};

class PermissionDenied : public LEOSACException
{
  public:
    PermissionDenied()
        : LEOSACException("Permission denied."){};
};

class InvalidCall : public LEOSACException
{
  public:
    InvalidCall()
        : LEOSACException("Unknown message type."){};
};

class SessionAborted : public LEOSACException
{
  public:
    SessionAborted();

    /**
     * Aborted due to invalid/expired token.
     * @param token
     * @return
     */
    SessionAborted(Auth::TokenPtr token);

  private:
    /**
     * Build an exception message for when the reason of the aborted
     * session is an expired token.
     */
    std::string build_msg(Auth::TokenPtr token) const;
};

class EntityNotFound : public LEOSACException
{
  public:
    /**
     * Construct the exception from a type that can be converted
     * to string using the `std::to_string()` call.
     */
    template <typename T>
    EntityNotFound(const T &id, const std::string &type)
        : EntityNotFound(std::to_string(id), type)
    {
    }

    EntityNotFound(const std::string &id, const std::string &type);

    const std::string &entity_id() const;
    const std::string &entity_type() const;

  private:
    std::string build_msg(const std::string &id, const std::string &type) const;

    std::string entity_id_;
    std::string entity_type_;
};
}
}
}
