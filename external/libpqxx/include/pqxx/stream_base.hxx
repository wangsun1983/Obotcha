/** Definition of the pqxx::stream_base class.
 *
 * pqxx::stream_base provides optimized batch access to a database table.
 *
 * DO NOT INCLUDE THIS FILE DIRECTLY; include stream_base instead.
 *
 * Copyright (c) 2001-2018, Jeroen T. Vermeulen.
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this mistake,
 * or contact the author.
 */
#ifndef PQXX_H_STREAM_BASE
#define PQXX_H_STREAM_BASE

#include "compiler-public.hxx"
#include "compiler-internal-pre.hxx"
#include "transaction_base.hxx"
#include "util.hxx"

#include <string>


namespace pqxx
{

class PQXX_LIBEXPORT PQXX_NOVTABLE stream_base :
  public internal::transactionfocus
{
public:
  explicit stream_base(transaction_base &);
  virtual ~stream_base() noexcept;
  virtual void complete() = 0;
  operator bool() const noexcept;
  bool operator!() const noexcept;
protected:
  bool m_finished;
  virtual void close();
  template<typename C> static std::string columnlist(const C &);
  template<typename I> static std::string columnlist(I begin, I end);
private:
  stream_base();
  stream_base(const stream_base&);
  stream_base & operator=(const stream_base &);
};

template<typename C> std::string stream_base::columnlist(const C &c)
{
  return columnlist(std::begin(c), std::end(c));
}

template<typename I> std::string stream_base::columnlist(I begin, I end)
{
  return separated_list(",", begin, end);
}

} // namespace pqxx


#include "compiler-internal-post.hxx"
#endif
