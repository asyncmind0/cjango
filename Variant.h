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

#ifndef _VARIANT_H
#define	_VARIANT_H

#include <cassert>
#include <typeinfo>

// FIXME: Make this thread-safe. Likely at the cost of reference counting.

class Variant {
public:
    Variant()
        : m_data(0)
    {
    }

    Variant(const Variant& variant)
        : m_data(variant.m_data)
    {
        if (m_data)
            dataRef();
    }

    template <typename Type>
    Variant(const Type& value)
        : m_data(0)
    {
        set(value);
    }
    
    ~Variant()
    {
        if (m_data)
            dataDeref();
    }

    bool isNull() const
    {
        return !m_data;
    }
    
    template <typename Type>
    bool is() const
    {
        if (!m_data)
            return typeid(Type) == typeid(void);
        return m_data->type() == typeid(Type);
    }

    const std::type_info& type() const
    {
        if (!m_data)
            return typeid(void);
        return m_data->type();
    }

    void reset()
    {
        if (m_data)
            dataDeref();
    }

    template <typename Type>
    Type get() const
    {
        if (!is<Type>())
            return Type();
        
        Data<Type>* data = static_cast<Data<Type>*>(m_data);
        return data->value();
    }

    template <typename Type>
    void set(const Type& value)
    {
        if (is<Type>() && m_data->isMutable()) {
            Data<Type>* data = static_cast<Data<Type>*>(m_data);
            data->setValue(value);
        } else {
            if (m_data)
                dataDeref();
            m_data = new Data<Type>(value);
            dataRef();
        }
    }

    Variant& operator=(const Variant& variant)
    {
        if (m_data == variant.m_data)
            return *this;
        
        if (m_data)
            dataDeref();
        m_data = variant.m_data;
        if (m_data)
            dataRef();
        return *this;
    }

    bool operator==(const Variant& variant) const
    {
        if (m_data == variant.m_data)
            return true;
        if (!m_data || !variant.m_data)
            return false;
        return type() == variant.type() && m_data->valueEquals(variant.m_data);
    }

    bool operator!=(const Variant& variant) const
    {
        return !operator==(variant);
    }

private:
   class AbstractData {
    public:
        AbstractData()
            : m_refCount(0)
        {
        }

        virtual ~AbstractData()
        {
        }

        void ref()
        {
            ++m_refCount;
            assert(m_refCount > 0);
        }

        bool deref()
        {
            assert(m_refCount > 0);
            --m_refCount;
            return m_refCount == 0;
        }

        bool isMutable() const
        {
            assert(m_refCount > 0);
            return m_refCount == 1;
        }

        virtual const std::type_info& type() const = 0;

        virtual bool valueEquals(AbstractData* abstractData) const = 0;

    protected:
        int m_refCount;
    };

    template <typename Type>
    class Data : public AbstractData {
    public:
        Data(const Type& value)
            : AbstractData()
        {
            setValue(value);
        }

        const std::type_info& type() const
        {
            return typeid(Type);
        }

        bool valueEquals(AbstractData* abstractData) const
        {
            assert(type() == abstractData->type());
            Data* data = static_cast<Data<Type>*>(abstractData);
            return m_value == data->m_value;
        }

        const Type& value() const
        {
            return m_value;
        }

        void setValue(const Type& value)
        {
            m_value = value;
        }

    private:
        Type m_value;
    };

    void dataRef()
    {
        assert(m_data);
        m_data->ref();
    }
    
    void dataDeref()
    {
        assert(m_data);
        if (m_data->deref())
            delete m_data;
        m_data = 0;
    }

    AbstractData* m_data;
};

#endif	/* _VARIANT_H */
