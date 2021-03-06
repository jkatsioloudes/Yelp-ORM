// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "Yelp-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy


#include <odb/mssql/traits.hxx>
#include <odb/mssql/database.hxx>
#include <odb/mssql/transaction.hxx>
#include <odb/mssql/connection.hxx>
#include <odb/mssql/statement.hxx>
#include <odb/mssql/statement-cache.hxx>
#include <odb/mssql/view-statements.hxx>
#include <odb/mssql/container-statements.hxx>
#include <odb/mssql/exceptions.hxx>
#include <odb/mssql/view-result.hxx>

namespace odb
{
  // StarCount
  //

  void access::view_traits_impl< ::StarCount, id_mssql >::
  bind (mssql::bind* b,
        image_type& i)
  {
    using namespace mssql;

    mssql::statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    std::size_t n (0);

    // stars
    //
    b[n].type = mssql::bind::int_;
    b[n].buffer = &i.stars_value;
    b[n].size_ind = &i.stars_size_ind;
    n++;

    // count
    //
    b[n].type = mssql::bind::int_;
    b[n].buffer = &i.count_value;
    b[n].size_ind = &i.count_size_ind;
    n++;
  }

  void access::view_traits_impl< ::StarCount, id_mssql >::
  init (view_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // stars
    //
    {
      int& v =
        o.stars;

      mssql::value_traits<
          int,
          mssql::id_int >::set_value (
        v,
        i.stars_value,
        i.stars_size_ind == SQL_NULL_DATA);
    }

    // count
    //
    {
      int& v =
        o.count;

      mssql::value_traits<
          int,
          mssql::id_int >::set_value (
        v,
        i.count_value,
        i.count_size_ind == SQL_NULL_DATA);
    }
  }

  result< access::view_traits_impl< ::StarCount, id_mssql >::view_type >
  access::view_traits_impl< ::StarCount, id_mssql >::
  query (database&, const query_base_type& q)
  {
    using namespace mssql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mssql::connection& conn (
      mssql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_view<view_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.image_binding ());

    if (im.version != sts.image_version () || imb.version == 0)
    {
      bind (imb.bind, im);
      sts.image_version (im.version);
      imb.version++;
    }

    const query_base_type& qs (q);
    qs.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        qs.clause (),
        false,
        true,
        qs.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::view_result_impl<view_type> > r (
      new (shared) mssql::view_result_impl<view_type> (
        qs, st, sts, 0));

    return result<view_type> (r);
  }

  // LastQueryTime
  //

  void access::view_traits_impl< ::LastQueryTime, id_mssql >::
  bind (mssql::bind* b,
        image_type& i)
  {
    using namespace mssql;

    mssql::statement_kind sk (statement_select);
    ODB_POTENTIALLY_UNUSED (sk);

    std::size_t n (0);

    // text
    //
    b[n].type = mssql::bind::string;
    b[n].buffer = &i.text_value;
    b[n].size_ind = &i.text_size_ind;
    b[n].capacity = static_cast<SQLLEN> (sizeof (i.text_value));
    n++;

    // elapsed_time
    //
    b[n].type = mssql::bind::bigint;
    b[n].buffer = &i.elapsed_time_value;
    b[n].size_ind = &i.elapsed_time_size_ind;
    n++;
  }

  void access::view_traits_impl< ::LastQueryTime, id_mssql >::
  init (view_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // text
    //
    {
      ::std::string& v =
        o.text;

      mssql::value_traits<
          ::std::string,
          mssql::id_string >::set_value (
        v,
        i.text_value,
        static_cast<std::size_t> (i.text_size_ind),
        i.text_size_ind == SQL_NULL_DATA);
    }

    // elapsed_time
    //
    {
      long int& v =
        o.elapsed_time;

      mssql::value_traits<
          long int,
          mssql::id_bigint >::set_value (
        v,
        i.elapsed_time_value,
        i.elapsed_time_size_ind == SQL_NULL_DATA);
    }
  }

  access::view_traits_impl< ::LastQueryTime, id_mssql >::query_base_type
  access::view_traits_impl< ::LastQueryTime, id_mssql >::
  query_statement (const query_base_type& q)
  {
    query_base_type r (
      "select top 1 text, last_elapsed_time from sys.dm_exec_query_stats cross apply sys.dm_exec_sql_text(sql_handle) order by last_execution_time desc");

    if (!q.empty ())
    {
      r += " ";
      r += q.clause_prefix ();
      r += q;
    }

    return r;
  }

  result< access::view_traits_impl< ::LastQueryTime, id_mssql >::view_type >
  access::view_traits_impl< ::LastQueryTime, id_mssql >::
  query (database&, const query_base_type& q)
  {
    using namespace mssql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    mssql::connection& conn (
      mssql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_view<view_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.image_binding ());

    if (im.version != sts.image_version () || imb.version == 0)
    {
      bind (imb.bind, im);
      sts.image_version (im.version);
      imb.version++;
    }

    const query_base_type& qs (query_statement (q));
    qs.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        conn,
        qs.clause (),
        false,
        true,
        qs.parameters_binding (),
        imb));

    st->execute ();

    shared_ptr< odb::view_result_impl<view_type> > r (
      new (shared) mssql::view_result_impl<view_type> (
        qs, st, sts, 0));

    return result<view_type> (r);
  }
}

#include <odb/post.hxx>
