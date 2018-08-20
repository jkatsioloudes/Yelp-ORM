// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef YELP_ODB_HXX
#define YELP_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "Yelp.hpp"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/view-image.hxx>
#include <odb/view-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // StarCount
  //
  template <>
  struct class_traits< ::StarCount >
  {
    static const class_kind kind = class_view;
  };

  template <>
  class access::view_traits< ::StarCount >
  {
    public:
    typedef ::StarCount view_type;
    typedef ::StarCount* pointer_type;

    static void
    callback (database&, view_type&, callback_event);
  };

  // LastQueryTime
  //
  template <>
  struct class_traits< ::LastQueryTime >
  {
    static const class_kind kind = class_view;
  };

  template <>
  class access::view_traits< ::LastQueryTime >
  {
    public:
    typedef ::LastQueryTime view_type;
    typedef ::LastQueryTime* pointer_type;

    static void
    callback (database&, view_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/mssql/version.hxx>
#include <odb/mssql/forward.hxx>
#include <odb/mssql/binding.hxx>
#include <odb/mssql/mssql-types.hxx>
#include <odb/mssql/query.hxx>

namespace odb
{
  // StarCount
  //
  template <>
  class access::view_traits_impl< ::StarCount, id_mssql >:
    public access::view_traits< ::StarCount >
  {
    public:
    struct image_type
    {
      // stars
      //
      int stars_value;
      SQLLEN stars_size_ind;

      // count
      //
      int count_value;
      SQLLEN count_size_ind;

      std::size_t version;

      mssql::change_callback change_callback_;

      mssql::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    typedef mssql::view_statements<view_type> statements_type;

    typedef mssql::query_base query_base_type;
    struct query_columns
    {
    };

    static const bool versioned = false;

    static void
    bind (mssql::bind*,
          image_type&);

    static void
    init (view_type&,
          const image_type&,
          database*);

    static const std::size_t column_count = 2UL;

    static result<view_type>
    query (database&, const query_base_type&);
  };

  template <>
  class access::view_traits_impl< ::StarCount, id_common >:
    public access::view_traits_impl< ::StarCount, id_mssql >
  {
  };

  // LastQueryTime
  //
  template <>
  class access::view_traits_impl< ::LastQueryTime, id_mssql >:
    public access::view_traits< ::LastQueryTime >
  {
    public:
    struct image_type
    {
      // text
      //
      char text_value[513];
      SQLLEN text_size_ind;

      // elapsed_time
      //
      long long elapsed_time_value;
      SQLLEN elapsed_time_size_ind;

      std::size_t version;

      mssql::change_callback change_callback_;

      mssql::change_callback*
      change_callback ()
      {
        return &change_callback_;
      }
    };

    typedef mssql::view_statements<view_type> statements_type;

    typedef mssql::query_base query_base_type;
    struct query_columns
    {
    };

    static const bool versioned = false;

    static void
    bind (mssql::bind*,
          image_type&);

    static void
    init (view_type&,
          const image_type&,
          database*);

    static const std::size_t column_count = 2UL;

    static query_base_type
    query_statement (const query_base_type&);

    static result<view_type>
    query (database&, const query_base_type&);
  };

  template <>
  class access::view_traits_impl< ::LastQueryTime, id_common >:
    public access::view_traits_impl< ::LastQueryTime, id_mssql >
  {
  };
}

#include "Yelp-odb.ixx"

#include <odb/post.hxx>

#endif // YELP_ODB_HXX