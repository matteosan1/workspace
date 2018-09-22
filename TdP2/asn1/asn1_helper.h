#ifndef ASN1_HELPER_HPP
#define ASN1_HELPER_HPP

#include "include/asn_application.h"
#include "include/BOOLEAN.h"
#include "include/INTEGER.h"
#include "include/ENUMERATED.h"    // for: setField<ENUMERATED_t>
#include "include/OCTET_STRING.h"
#include "include/GeneralizedTime.h"
#include "include/asn_SET_OF.h"
#include "include/asn_SEQUENCE_OF.h"

#include "per_decoder.h"
#include "per_encoder.h"

#include <QByteArray>
#include <QString>
#include <QDateTime>

#include <type_traits>

namespace asn1_wtu {

#define ASN1C_TYPE(T) asn_DEF_##T

template <typename T>
class asn_struct;

namespace Impl
{
    /**
     * \brief Helper function fill a \c QByteArray from a raw buffer
     * \param[in] buffer Source buffer
     * \param[in] size Size of the buffer
     * \param[out] app_key Pointer to the \c QByteArray object to fill
     * \return The buffer size
     */
    inline int fill_fn(const void *buffer, size_t size, void *appKey)
    {
        QByteArray *ba = static_cast<QByteArray *>(appKey);
        if (!ba)
            return -1;

        ba->append((const char *) buffer, size);
        return size;
    }
}

template <typename T>
void operator <<(T & first, const asn_struct<T> & second);

// ---------------------------- BEGIN DER/BER SECTION ------------------------- //

/**
 * \brief Encodes an ASN1 struct.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] m ASN1 object to encode.
 * \return Encoded byte array, empty in case of errors.
 */
inline
QByteArray asn_encode(asn_TYPE_descriptor_t &asnDef, const void *m)
{
    QByteArray buf;
    const asn_enc_rval_t er = der_encode(&asnDef, (void*)m, Impl::fill_fn, &buf);
    return er.encoded < 0 ? QByteArray() : buf;
}

template <typename T>
QByteArray asn_encode(const asn_struct<T> &m)
{
    if ( !m )
        return QByteArray();

    return asn_encode(*m.getTypeDescriptor(), &*m);
}

/**
 * \brief Decodes an ASN1 buffer.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] buf ASN1 buffer to dencode.
 * \return A pointer to a newly allocated ASN1 struct, null in case of errors.
 */
template <typename T>
asn_struct<T> decodeStruct(asn_TYPE_descriptor_t &asnDef, const QByteArray &buf)
{
    if (buf.isEmpty())
        return asn_struct<T>();

    T *m = 0;
    const asn_dec_rval_t dr = ber_decode(0, &asnDef, (void**)&m, buf.data(), buf.size());

    if (dr.code != RC_OK) {
        // free partially decoded message
        asnDef.free_struct(&asnDef, m, 0);
        return asn_struct<T>();
    }

    return asn_struct<T>::fromRawData(&asnDef, m);
}

#define asn_decode(T, m) \
    decodeStruct<T>(ASN1C_TYPE(T), m)

/**
 * \brief Prints an ASN1 struct.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] m ASN1 object to print.
 * \return A byte array containing an XML representation of the passed ASN1 object.\n
 *         Returns an empty byte array in case of errors.
 */
template <typename T>
QString asn_print(const asn_struct<T> &m)
{
    if ( !m )
        return QString();

    auto m2 = decodeStruct<T>(*m.getTypeDescriptor(), asn_encode(m));
    if ( !m2 )
        return QString();

    QByteArray buf;
    const asn_enc_rval_t er = xer_encode(m2.getTypeDescriptor(), (void*)(&*m2), XER_F_BASIC, Impl::fill_fn, &buf);

    return er.encoded < 0 ? QString() : QString(buf);
}

// ---------------------------- END DER/BER SECTION ------------------------- //

// ---------------------------- BEGIN UPER SECTION ------------------------- //

/**
 * \brief Encodes an ASN1 struct.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] m ASN1 object to encode.
 * \return Encoded byte array, empty in case of errors.
 */
template <typename T>
QByteArray asn_uper_encode(const asn_struct<T> &m)
{
    QByteArray buf;
    const asn_enc_rval_t er = uper_encode(m.getTypeDescriptor(), (void*)(&*m), Impl::fill_fn, &buf);

    return er.encoded < 0 ? QByteArray() : buf;
}

/**
 * \brief Decodes an ASN1 buffer.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] buf ASN1 buffer to dencode.
 * \return A pointer to a newly allocated ASN1 struct, null in case of errors.
 */
template <typename T>
asn_struct<T> decodeStruct_uper(asn_TYPE_descriptor_t &asnDef, const QByteArray &buf, int* consumed=NULL)
{
    if (buf.isEmpty())
        return asn_struct<T>();

    T *m = 0;
    const asn_dec_rval_t dr = uper_decode_complete(0, &asnDef, (void**)&m, buf.data(), buf.size());

    if (dr.code != RC_OK) {
        // free partially decoded message
        asnDef.free_struct(&asnDef, m, 0);
        return asn_struct<T>();
    }

    if(consumed != NULL)
        *consumed = dr.consumed;

    return asn_struct<T>::fromRawData(&asnDef, m);
}

#define asn_uper_decode(T, m, ...) \
    decodeStruct_uper<T>(ASN1C_TYPE(T), m, ##__VA_ARGS__)

/**
 * \brief Prints an ASN1 struct.
 * \param[in] asn_def ASN1C type-specific object definition.
 * \param[in] m ASN1 object to print.
 * \return A byte array containing an XML representation of the passed ASN1 object.\n
 *         Returns an empty byte array in case of errors.
 */
template <typename T>
QByteArray asn_print_uper(const asn_struct<T> &m)
{
    QByteArray buf;
    const asn_enc_rval_t er = uper_encode(m.getTypeDescriptor(), (void*)(&*m), XER_F_BASIC, Impl::fill_fn, &buf);

    return er.encoded < 0 ? QByteArray() : buf;
}

// ---------------------------- END UPER SECTION ------------------------- //


/**
 * @brief This class provides an interface to read from asn1c struct fields.
 *
 * Each specialization of this type provides a way to convert from asn1c types
 * to Qt types avoiding clients to worry about resource management.
 *
 * @param T The type to be read from.
 */
template <typename R, typename T, typename Check = void>
struct getField
{
    static_assert(!std::is_same<T, T>::value, "getField not implemented for this type");
};

template <>
struct getField<bool, BOOLEAN_t>
{
    bool operator()(const BOOLEAN_t *field, bool *ok)
    {
        *ok = true;
        return !!*field;
    }
};

template <>
struct getField<long, INTEGER_t>
{
    long operator()(const INTEGER_t *field, bool *ok)
    {
        long ret;
        if (asn_INTEGER2long(field, &ret) == 0) {
            *ok = true;
            return ret;
        } else {
            // Let's return true when the struct is just emtpy
            *ok = errno == EINVAL;
            return 0;
        }
    }
};

template <>
struct getField<int, INTEGER_t>
{
    int operator()(const INTEGER_t *field, bool *ok)
    {
        return getField<long, INTEGER_t>()(field, ok);
    }
};


template <>
struct getField<unsigned long, INTEGER_t>
{
    unsigned long operator()(const INTEGER_t *field, bool *ok)
    {
        unsigned long ret;
        if (asn_INTEGER2ulong(field, &ret) == 0) {
            *ok = true;
            return ret;
        } else {
            // Let's return true when the struct is just emtpy
            *ok = errno == EINVAL;
            return 0;
        }
    }
};

template <>
struct getField<unsigned int, INTEGER_t>
{
    int operator()(const INTEGER_t *field, bool *ok)
    {
        return getField<unsigned long, INTEGER_t>()(field, ok);
    }
};

template <>
struct getField<QByteArray, OCTET_STRING_t>
{
    QByteArray operator()(const OCTET_STRING_t *field, bool *ok)
    {
        *ok = true;
        return QByteArray((const char*)field->buf, field->size);
    }
};

template <>
struct getField<QString, OCTET_STRING_t>
{
    QString operator()(const OCTET_STRING_t *field, bool *ok)
    {
        return QString::fromUtf8(getField<QByteArray, OCTET_STRING_t>()(field, ok));
    }
};

template <>
struct getField<QDateTime, GeneralizedTime_t>
{
    QDateTime operator()(const GeneralizedTime_t *field, bool *ok)
    {
        const QByteArray buf = getField<QByteArray, OCTET_STRING_t>()(field, ok);

        QDateTime dt;
        if (buf.size() == 11)
            dt = QDateTime::fromString(buf, "yyyyMMddhhZ");
        else if (buf.size() == 13)
            dt = QDateTime::fromString(buf, "yyyyMMddhhmmZ");
        else if (buf.size() == 15)
            dt = QDateTime::fromString(buf, "yyyyMMddhhmmssZ");
        else
            dt = QDateTime::fromString(buf, "yyyyMMddhhmmss.zZ");

        dt.setTimeSpec(Qt::UTC);
        return dt.toLocalTime();
    }
};

template <typename R, typename T>
struct getField<R, T, typename std::enable_if<std::is_enum<R>::value>::type>
{
    R operator()(const T* field, bool *ok)
    {
        auto result = getField<int, T>()(field, ok);
        return static_cast<R>(result);
    }
};

template <typename T>
struct getField<asn_struct<T>, T>
{
    asn_struct<T> operator()(const T* field, asn_TYPE_descriptor_t * asnDef, bool *ok)
    {
        *ok = true;
        return asn_struct<T>(asnDef, field);
    }
};

template <typename R, typename T>
inline R asn_get_field(const T *field, bool *ok = nullptr)
{
    bool iok;
    return getField<R, T>()(field, ok ? ok : &iok);
}

template <typename R, typename T>
inline R asn_get_field(T * const *field, bool *ok = nullptr)
{
    bool iok;
    if (*field) {
        return getField<R, T>()(*field, ok ? ok : &iok);
    } else {
        if (ok)
            *ok = false;
        return R();
    }
}

template <typename T>
inline asn_struct<T> asn_get_field(const T *field, asn_TYPE_descriptor_t * asnDef, bool *ok = nullptr)
{
    bool iok;
    return getField<asn_struct<T>,T>()(field, asnDef, ok ? ok : &iok);
}

#define asn_get_wrapped_field(T, field, ...) \
        asn_get_field<T>(field, &ASN1C_TYPE(T) , ## __VA_ARGS__)

/**
 * @brief This class provides an interface to write to asn1c struct fields.
 *
 * Each specialization of this type provides a way to write to asn1c types
 * from Qt types avoiding clients to worry about resource management.
 *
 * @tparam T The type to write to.
 */
template <typename T>
struct setField
{
    bool operator()(T * field, const asn_struct<T> & value)
    {
        if ( !field )
            return false;
        *field << value;
        return true;
    }

    bool operator()(T * field, T value)
    {
        if ( !field )
            return false;
        *field = value;
        return true;
    }
};


template <>
struct setField<BOOLEAN_t>
{
    bool operator()(BOOLEAN_t *field, bool value)
    {
        *field = (BOOLEAN_t)value;
        return true;
    }
};

template <>
struct setField<INTEGER_t>
{
    bool operator()(INTEGER_t *field, long value)
    {
        return asn_long2INTEGER(field, value) == 0;
    }

    bool operator()(INTEGER_t *field, int value)
    {
        return operator()(field, (long)value);
    }

    bool operator()(INTEGER_t *field, unsigned long value)
    {
        return asn_ulong2INTEGER(field, value) == 0;
    }

    bool operator()(INTEGER_t *field, unsigned int value)
    {
        return operator()(field, (unsigned long)value);
    }
};

template <>
struct setField<OCTET_STRING_t>
{
    bool operator()(OCTET_STRING_t *field, const QByteArray &value)
    {
        return OCTET_STRING_fromBuf(field, value.data(), value.size()) == 0;
    }

    bool operator()(OCTET_STRING_t *field, const QString &value)
    {
        return operator()(field, value.toUtf8());
    }

    bool operator()(OCTET_STRING_t *field, const char * value)
    {
        return operator()(field, QString(value));
    }

    bool operator()(GeneralizedTime_t *field, const QDateTime &value)
    {
        return operator()(field, value.toUTC().toString("yyyyMMddhhmmss.zZ").toLatin1());
    }
};

template <typename X, typename Y>
inline bool asn_set_field(X *field, Y value)
{
    return setField<X>()(field, value);
}

template <typename X, typename Y>
inline bool asn_set_field(X **field, Y value)
{
    if (!*field)
        *field = static_cast<X*>(calloc(1, sizeof(X)));
    if (!*field)
        return false;
    else
        return setField<X>()(*field, value);
}

template <typename X>
inline bool asn_set_field(X **field, asn_TYPE_descriptor_t *asnDef)
{
    if (*field) {
        asnDef->free_struct(asnDef, *field, 0);
        *field = 0;
    }

    return true;
}

// SET_OF FUNCTIONS

template <typename T>
inline int asn_setof_size(const T* field)
{
    return field->list.count;
}

template <typename R, typename T>
inline R asn_setof_get_item(const T * field, int id, bool *ok = nullptr)
{
    if ( id < 0 || id >= asn_setof_size(field) ) {
        if (ok)
            *ok = false;
        return R();
    }
    bool iok;
    return getField<R, typename std::remove_reference<decltype(**(field->list.array))>::type>()(field->list.array[id], ok ? ok : &iok);
}

template <typename R, typename T>
inline R asn_setof_get_item(const T *field, asn_TYPE_descriptor_t * asnDef, int id, bool *ok = nullptr)
{
    if ( id < 0 || id >= asn_setof_size(field) ) {
        if (ok)
            *ok = false;
        return R();
    }
    bool iok;
    return asn_get_field(field->list.array[id], asnDef, ok ? ok : &iok);
}

#define asn_setof_get_wrapped_item(R, field, id, ...) \
        asn_setof_get_item<asn_struct<R>>(field, &ASN1C_TYPE(R), id, ## __VA_ARGS__)

template <typename X, typename Y>
inline bool asn_setof_set_item(X * field, int id, Y value)
{
    if ( id < 0 || id >= asn_setof_size(field) )
        return false;
    return asn_set_field(&field->list.array[id], value);
}

template <typename X, typename Y>
inline bool asn_setof_add_item(X * field, Y value)
{
    typename std::remove_reference<decltype(*(field->list.array))>::type tmpValue = nullptr;
    if (!asn_set_field(&tmpValue, value))
        return false;

    return asn_set_add(field, tmpValue) == 0;
}

#define asn_setof_remove_item(T, field, id) \
    asn_setof_remove_item_impl( &ASN1C_TYPE(T), field, id )

template <typename T>
inline void asn_setof_remove_item_impl(asn_TYPE_descriptor_t * def, T * field, int id)
{
    if ( id < 0 || id >= asn_setof_size(field) )
        return;

    auto ptr = field->list.array[id];
    asn_set_del(field, id, 0);
    def->free_struct(def, ptr, 0);
}

#define asn_setof_empty(T, field) \
    asn_setof_empty_impl( &ASN1C_TYPE(T), field )

template <typename T>
inline void asn_setof_empty_impl(asn_TYPE_descriptor_t * def, T* field)
{
    for ( int i = 0; i < asn_setof_size(field); ++i )
        def->free_struct(def, field->list.array[i], 0);

    field->list.count = 0;
}


// SEQUENCE_OF FUNCTIONS

template <typename R, typename T>
inline R asn_sequenceof_get_item(const T * field, int id, bool *ok = nullptr)
{
    return asn_setof_get_item<R>(field, id, ok);
}

#define asn_sequenceof_get_wrapped_item(R, field, id, ...) \
        asn_setof_get_wrapped_item(R, field, id, ## __VA_ARGS__)

template <typename X, typename Y>
inline bool asn_sequenceof_set_item(X * field, int id, Y value)
{
    return asn_setof_set_item(field, id, value);
}

template <typename X, typename Y>
inline bool asn_sequenceof_add_item(X * field, Y value)
{
    return asn_setof_add_item(field, value);
}

#define asn_sequenceof_remove_item(T, field, id) \
    asn_sequenceof_remove_item_impl(&ASN1C_TYPE(T), field, id)

template <typename T>
inline void asn_sequenceof_remove_item_impl(asn_TYPE_descriptor_t * def, T * field, int id)
{
    if (id < 0 || id >= asn_sequenceof_size(field))
        return;

    auto ptr = field->list.array[id];
    asn_sequence_del(field, id, 0);
    def->free_struct(def, ptr, 0);
}

template <typename T>
inline int asn_sequenceof_size(const T* field)
{
    return asn_setof_size(field);
}

#define asn_sequenceof_empty(T, field) \
    asn_setof_empty_impl(&ASN1C_TYPE(T), field)



/**
 * @brief A struct wrapping asn1c types.
 *
 * This class manages and frees automatically an underlying pointer to an asn1
 * type which has been created by asn1 syntax and the asn1c tool.
 *
 * @tparam T The type wrapped.
 */
template <typename T>
class asn_struct
{
    public:
        /**
         * @brief Constructs a \ref asn_struct object that uses the raw asn1 pointer \c m.
         *
         * The passed underlying asn1 object \c m is *NOT* copied.
         *
         * @param asnDef A pointer to the corresponding DEF asn1c instance.
         * @param m A pointer to the underlying struct.
         */
        static asn_struct<T> fromRawData(asn_TYPE_descriptor_t * asnDef, T * m)
        {
            asn_struct<T> t;
            t.asnDef_ = asnDef;
            t.struct_ = m;
            return t;
        }

        /**
         * @brief Constructs a \ref asn_struct object with the passed asn1 pointer \c m.
         *
         * The specified underlying structure \c m is copied.
         *
         * @param asnDef A pointer to the corresponding DEF asn1c instance.
         * @param m A pointer to the underlying struct.
         */
        asn_struct(asn_TYPE_descriptor_t *asnDef, const T *m) :
            struct_(nullptr), asnDef_(nullptr)
        {
            Q_ASSERT_X(asnDef && m,
                "asn_struct(asn_TYPE_descriptor_t *asnDef, const T *m)",
                "Input values were null");

            *this = decodeStruct<T>(*asnDef, asn_encode(*asnDef, m));

            Q_ASSERT_X(asnDef_ && struct_,
                "asn_struct(asn_TYPE_descriptor_t *asnDef, const T *m)",
                "could not create a valid ASN1 structure");
        }

        /**
         * @brief Basic constructor.
         *
         * This creates an empty shell, useful as a placeholder to signal
         * that a decoding didn't go well, or in general that this struct
         * does not contain anything.
         */
        asn_struct() : struct_(nullptr), asnDef_(nullptr)
        {
        }

        /**
         * @brief Basic constructor.
         *
         * Allocates and zeros a new instance of the wrapped type.
         *
         * @param asnDef A pointer (not managed) to the corresponding DEF asn1c instance.
         */
        asn_struct(asn_TYPE_descriptor_t * asnDef) : asnDef_(asnDef)
        {
            struct_ = static_cast<T*>(calloc(1, sizeof(T)));

            Q_ASSERT_X(struct_,
                    "asn_struct(asn_TYPE_descriptor_t * asnDef)",
                    "calloc created no memory!");
        }

        /**
         * @brief Basic destructor.
         *
         * If needed, frees the underlying instance via ans1c functions.
         */
        ~asn_struct()
        {
            if ( struct_ ) {
                Q_ASSERT_X(asnDef_,
                        "~asn_struct()",
                        "destructor missing asnDef_ to free struct!");
                asnDef_->free_struct(asnDef_, struct_, 0);
            }
        }

        /**
         * @brief Copy constructor.
         *
         * This constructor is probably pretty intensive. To avoid memory leaks
         * it simply encodes the struct into a QByteArray, and instantly
         * decodes it. The result becomes the new object.
         *
         * @param other The asn_struct to copy.
         */
        asn_struct(const asn_struct<T> & other) : struct_(nullptr)
        {
            if ( other.asnDef_ ) {
                Q_ASSERT_X(other.struct_,
                        "asn_struct(const asn_struct<T> & other)",
                        "copy constructor, other parameter did not have struct_ allocated");

                *this = decodeStruct<T>(*other.asnDef_, asn_encode(other));

                Q_ASSERT_X(asnDef_ && struct_,
                    "asn_struct(const asn_struct<T> & other)",
                    "could not create a valid ASN1 structure");
            }
            else
                *this = asn_struct();
        }

        /**
         * @brief Move constructor.
         *
         * @param other The asn_struct to move resources from.
         */
        asn_struct(asn_struct<T> && other) : struct_(other.struct_), asnDef_(other.asnDef_)
        {
            other.struct_ = nullptr;
            other.asnDef_ = nullptr;
        }

        /**
         * @brief Copy/Move assignment.
         *
         * @param other the asn_struct to copy/move from.
         *
         * @return
         */
        asn_struct & operator=(asn_struct<T> other)
        {
            swap(*this, other);
            return *this;
        }

        /**
         * @brief Equality operator.
         *
         * @param other the asn_struct to compare.
         *
         * @return \c true if the asn1 encoded byte arrays are equal.
         */
        bool operator==(const asn_struct<T> &other) const
        {
            return asn_encode(*this) == asn_encode(other);
        }

        /**
         * @brief Inequality operator.
         *
         * @param other the asn_struct to compare.
         *
         * @return \c true if the asn1 encoded byte arrays are different.
         */
        bool operator!=(const asn_struct<T> &other) const
        {
            return !operator==(other);
        }

        /**
         * @brief Returns a reference to the underlying asn1 struct.
         */
        T & operator*()
        {
            return *struct_;
        }

        /**
         * @brief Returns a reference to the underlying asn1 struct.
         */
        const T & operator*() const
        {
            return *struct_;
        }

        /**
         * @brief Dereferences the underlying asn1 struct.
         */
        T * operator->()
        {
            return struct_;
        }

        /**
         * @brief Dereferences the underlying asn1 struct.
         */
        const T * operator->() const
        {
            return struct_;
        }

        /**
         * @brief Returns whether there is an asn1 struct.
         *
         * This function is useful when checking whether a decoding was
         * successful.
         */
        operator bool() const
        {
            return struct_;
        }

        /**
         * @brief Gets the asn1 type that describes the underlying asn1 struct.
         */
        asn_TYPE_descriptor_t * getTypeDescriptor() const
        {
            return asnDef_;
        }

    private:
        static void swap(asn_struct<T> & first, asn_struct<T> & second)
        {
            using std::swap;

            swap(first.struct_, second.struct_);
            swap(first.asnDef_, second.asnDef_);
        }

        static void swap(asn_struct<T> &first, T & second)
        {
            T tmp = second;
            second = *first;
            *first = tmp;
        }

        T * struct_;
        asn_TYPE_descriptor_t * asnDef_;

        friend void operator << <T>(T & first, const asn_struct<T> & second);
};

template <typename T>
void operator <<(T & first, const asn_struct<T> & second)
{
    auto tmp = second;
    asn_struct<T>::swap(tmp, first);
}

#define asn_make_struct(T, ...) \
    asn_struct<T>(&ASN1C_TYPE(T), ## __VA_ARGS__)



// High level helper macros

#define asn1make(T, ...) \
    asn_make_struct(T, ## __VA_ARGS__)

#define asn1get(raw_struct, field, type) \
    asn_get_field<type>(&((raw_struct)->field))

#define asn1set(raw_struct, field, val) \
    asn_set_field(&((raw_struct)->field), val)

#define asn1clr(raw_struct, field, T) \
    asn_set_field(&((raw_struct)->field), &ASN1C_TYPE(T))

}

#endif // ASN1_HELPER_HPP
