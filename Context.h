/**
 * Copyright (C) 2010  Jakub Wieczorek <fawek@fawek.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONTEXT_H
#define	_CONTEXT_H

#include "Variant.h"

#include <string>
#include <tr1/unordered_map>
#include <vector>

typedef std::tr1::unordered_map<std::string, Variant> VariableMap;

class Context {
public:
    Context(const VariableMap& variables = VariableMap());
    ~Context();

    void push();
    void pop();

    bool contains(const std::string& key) const;
    const Variant& get(const std::string& key) const;
    void set(const std::string& key, const Variant& variant);
    void remove(const std::string& key);

private:
    std::vector<VariableMap> m_variableStack;
};

#endif	/* _CONTEXT_H */
