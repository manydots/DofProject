#pragma once
/**
 * The MIT License (MIT)
 * Copyright (c) 2019-2020, Gaaagaa All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

 /**
  * @file xini_file.h
  * Copyright (c) 2019-2020, Gaaagaa All rights reserved.
  *
  * @author  ：Gaaagaa
  * @date    : 2021-01-09
  * @version : 1.2.0.1
  * @brief   : `this->operator __base_type()`, gcc not supported.
  * @note    : Sepecial thanks for (qinwanlin)[https://gitee.com/qinwanlin].
  *
  * @author  ：Gaaagaa
  * @date    : 2020-11-07
  * @version : 1.2.0.0
  * @brief   : Improved retrieval performance of the operator[].
  *
  * @author  ：Gaaagaa
  * @date    : 2020-10-28
  * @version : 1.1.0.0
  * @brief   : update load()/release(), add operator()/try_value().
  *
  * @author  ：Gaaagaa
  * @date    : 2019-11-26
  * @version : 1.0.0.0
  * @brief   : ini file parser, read and write is supported.
  */
#pragma once
#ifndef __XINI_FILE_H__
#define __XINI_FILE_H__

#include <list>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

  ////////////////////////////////////////////////////////////////////////////////
  // xini_node_t : INI 节点的抽象定义

  /**
   * <pre>
   * INI 文件格式的结构如下：
   * [文件根]
   *     |--[空行]
   *     |--[注释]
   *     +--[分节]
   *         |--[空行]
   *         |--[注释]
   *         |--[键值]
   *         |--[键值]
   *         |--[空行]
   *         |--[空行]
   *         |--[...]
   *     |--[空行]
   *     |--[空行]
   *     |--[空行]
   *     +--[分节]
   *           |--[空行]
   *           |--[注释]
   *           |--[键值]
   *           |--[空行]
   *           |--[键值]
   *           |--[键值]
   *           |--[键值]
   *           |--[空行]
   *           |--[...]
   *     |--[空行]
   *     |--[...]
   *
   * 文件根：INI 文件的虚拟名称，不存在于文件内容中。
   * 空行：空白行，即便有空白字符占据，也算空白行。
   * 注释：以 “;” 或者 “#” 开头后的内容，都算是注释内容。
   * 分节：格式为 “[section]” 。
   * 键值：格式为 “key=value” 。
   * </pre>
   */

   /**
    * @enum  xini_node_type_t
    * @brief INI 文件中的节点信息类型。
    */
typedef enum xini_ntype_t
{
    XINI_NTYPE_UNDEFINE = 0xFFFFFFFF, ///< 未定义
    XINI_NTYPE_FILEROOT = 0x00000000, ///< 文件根
    XINI_NTYPE_NILLINE = 0x00000100, ///< 空行
    XINI_NTYPE_COMMENT = 0x00000200, ///< 注释
    XINI_NTYPE_SECTION = 0x00000300, ///< 分节
    XINI_NTYPE_KEYVALUE = 0x00000400, ///< 键值
} xini_ntype_t;

/** 前置声明相关的 INI 节点类 */
class xini_keyvalue_t;
class xini_section_t;
class xini_comment_t;
class xini_nilline_t;
class xini_file_t;

/** 字符串修剪操作的默认字符集（空白字符集，以 isspace() 判断的字符为标准） */
static const char XCHARS_TRIM[] = " \t\n\r\f\v";

/**
 * @class xini_node_t
 * @brief INI 节点描述基类。
 */
class xini_node_t
{
    friend class xini_file_t;
    friend class xini_section_t;
    friend class xini_keyvalue_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 判断是否为单行字符串。
     */
    static inline bool is_sline(const std::string& xstr)
    {
        return (xstr.find_first_of("\r\n") == std::string::npos);
    }

    /**********************************************************/
    /**
     * @brief 判定字符串是否被修剪过。
     */
    static inline bool
        is_xtrim(
            const std::string& xstr,
            const char* xchars = XCHARS_TRIM)
    {
        std::string::size_type st_pos = xstr.find_first_of(xchars);
        return ((std::string::npos == st_pos) ||
            ((st_pos > 0) && (st_pos < (xstr.size() - 1))));
    }

    /**********************************************************/
    /**
     * @brief 修剪字符串前后端的字符集。
     */
    static inline std::string
        trim_xstr(
            const std::string& xstr,
            const char* xchars = XCHARS_TRIM)
    {
        std::string::size_type st_pos = xstr.find_first_not_of(xchars);
        if (std::string::npos != st_pos)
        {
            return xstr.substr(
                st_pos, xstr.find_last_not_of(xchars) - st_pos + 1);
        }

        return std::string("");
    }

    /**********************************************************/
    /**
     * @brief 修剪字符串前端的字符集。
     */
    static inline std::string
        trim_lstr(
            const std::string& xstr,
            const char* xchars = XCHARS_TRIM)
    {
        std::string::size_type st_pos = xstr.find_first_not_of(xchars);
        if (std::string::npos != st_pos)
        {
            return xstr.substr(st_pos);
        }

        return std::string("");
    }

    /**********************************************************/
    /**
     * @brief 修剪字符串后端的字符集。
     */
    static inline std::string
        trim_rstr(
            const std::string& xstr,
            const char* xchars = XCHARS_TRIM)
    {
        return xstr.substr(0, xstr.find_last_not_of(xchars));
    }

    /**********************************************************/
    /**
     * @brief 字符串忽略大小写的比对操作。
     *
     * @param [in ] xszt_lcmp : 比较操作的左值字符串。
     * @param [in ] xszt_rcmp : 比较操作的右值字符串。
     *
     * @return int
     *         - xszt_lcmp <  xszt_rcmp，返回 <= -1；
     *         - xszt_lcmp == xszt_rcmp，返回 ==  0；
     *         - xszt_lcmp >  xszt_rcmp，返回 >=  1；
     */
    static int xstr_icmp(const char* xszt_lcmp, const char* xszt_rcmp)
    {
        int xit_lvalue = 0;
        int xit_rvalue = 0;

        if (xszt_lcmp == xszt_rcmp)
            return 0;
        if (NULL == xszt_lcmp)
            return -1;
        if (NULL == xszt_rcmp)
            return 1;

        do
        {
            if (((xit_lvalue = (*(xszt_lcmp++))) >= 'A') && (xit_lvalue <= 'Z'))
                xit_lvalue -= ('A' - 'a');

            if (((xit_rvalue = (*(xszt_rcmp++))) >= 'A') && (xit_rvalue <= 'Z'))
                xit_rvalue -= ('A' - 'a');

        } while (xit_lvalue && (xit_lvalue == xit_rvalue));

        return (xit_lvalue - xit_rvalue);
    }

    /**
     * @struct xstr_icmp_t
     * @brief  as functor.
     */
    struct xstr_icmp_t
    {
        typedef std::string first_argument_type;
        typedef std::string second_argument_type;
        typedef bool        result_type;

        bool operator () (
            const std::string& xstr_left,
            const std::string& xstr_right) const
        {
            return (xstr_icmp(xstr_left.c_str(), xstr_right.c_str()) < 0);
        }
    };

    // constructor/destructor
protected:
    xini_node_t(int xini_ntype, xini_node_t* xowner_ptr)
        : m_xini_ntype(xini_ntype)
        , m_xowner_ptr(xowner_ptr)
    {

    }

    virtual ~xini_node_t(void)
    {

    }

    // extensible interfaces
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流，派生的子类中必须实现具体操作。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const = 0;

    /**********************************************************/
    /**
     * @brief 脏标识。
     */
    virtual bool is_dirty(void) const
    {
        if (NULL != m_xowner_ptr)
        {
            return m_xowner_ptr->is_dirty();
        }
        return false;
    }

    /**********************************************************/
    /**
     * @brief 设置脏标识。
     */
    virtual void set_dirty(bool x_dirty)
    {
        if (NULL != m_xowner_ptr)
        {
            m_xowner_ptr->set_dirty(x_dirty);
        }
    }

protected:
    /**********************************************************/
    /**
     * @brief 重命名附属的子节点（分节节点、键值节点）的索引名。
     */
    virtual bool rename_nsub(
        xini_node_t* xnsub_ptr,
        const std::string& xstr_name)
    {
        return false;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 节点类型。
     */
    inline int ntype(void) const { return m_xini_ntype; }

    /**********************************************************/
    /**
     * @brief 获取节点的持有者。
     */
    inline xini_node_t* get_owner(void) const { return m_xowner_ptr; }

    // data members
protected:
    int           m_xini_ntype;   ///< 节点类型
    xini_node_t* m_xowner_ptr;   ///< 节点持有者
};

/**********************************************************/
/**
 * @brief 定义 xini_node_t 的流输出操作符函数。
 */
inline std::ostream& operator << (
    std::ostream& ostr, const xini_node_t& xini_node)
{
    xini_node >> ostr;
    return ostr;
}

////////////////////////////////////////////////////////////////////////////////
// xini_nilline_t

/**
 * @class xini_nilline_t
 * @brief INI 文件中的空行节点类。
 */
class xini_nilline_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_nilline_t 对象。
     *
     * @param [in ] xstr_line  :
     *  用于创建 空行节点 的字符串行，
     *  其已经被 trim_xstr() 修剪前后端的空白字符。
     *
     * @param [in ] xowner_ptr :
     *  键值节点的拥有者（xini_section_t 类型）。
     *
     * @return xini_node_t * :
     *  操作成功，返回的 空行节点；若失败，则返回 NULL 。
     */
    static xini_node_t*
        try_create(
            const std::string& xstr_line,
            xini_node_t* xowner_ptr)
    {
        assert(is_xtrim(xstr_line));
        assert(is_sline(xstr_line));

        if (!xstr_line.empty())
        {
            return NULL;
        }

        return (new xini_nilline_t(xowner_ptr));
    }

    // construcor/destructor
protected:
    xini_nilline_t(xini_node_t* xowner_ptr)
        : xini_node_t(XINI_NTYPE_NILLINE, xowner_ptr)
    {

    }

    virtual ~xini_nilline_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const
    {
        ostr << std::endl;
        return *this;
    }
};

////////////////////////////////////////////////////////////////////////////////
// xini_comment_t

/**
 * @class xini_comment_t
 * @brief INI 文件中的 注释 节点类。
 */
class xini_comment_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_comment_t 对象。
     *
     * @param [in ] xstr_line  :
     *  用于创建 注释节点 的字符串行，
     *  其已经被 trim_xstr() 修剪前后端的空白字符。
     *
     * @param [in ] xowner_ptr :
     *  键值节点的拥有者（xini_section_t 类型）。
     *
     * @return xini_node_t * :
     *  操作成功，返回的 注释节点；若失败，则返回 NULL 。
     */
    static xini_node_t*
        try_create(
            const std::string& xstr_line,
            xini_node_t* xowner_ptr)
    {
        assert(is_xtrim(xstr_line));
        assert(is_sline(xstr_line));

        if (xstr_line.empty() ||
            ((';' != xstr_line.at(0)) && ('#' != xstr_line.at(0))))
        {
            return NULL;
        }

        xini_comment_t* xnode_ptr = new xini_comment_t(xowner_ptr);
        xnode_ptr->m_xstr_text = xstr_line;
        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_comment_t(xini_node_t* xowner_ptr)
        : xini_node_t(XINI_NTYPE_COMMENT, xowner_ptr)
    {

    }

    virtual ~xini_comment_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const
    {
        ostr << m_xstr_text << std::endl;
        return *this;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 注释行字符串 内容。
     */
    inline const std::string& text(void) const { return m_xstr_text; }

protected:
    std::string   m_xstr_text;  ///< 注释行字符串
};

////////////////////////////////////////////////////////////////////////////////
// xini_keyvalue_t

/**
 * @class xini_keyvalue_t
 * @brief INI 文件中的 分节 节点类。
 */
class xini_keyvalue_t : public xini_node_t
{
    friend class xini_file_t;
    friend class xini_section_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 检查键名字符串格式是否有效。
     *
     * @param [in ] xstr_name :
     *  待检查的 键名，其已经被 trim_xstr() 修剪过前后端的空白字符。
     */
    static bool check_kname(const std::string& xstr_name)
    {
        assert(is_xtrim(xstr_name));

        if (xstr_name.empty())
        {
            return false;
        }

        if (std::string::npos != xstr_name.find_first_of(";#=\r\n"))
        {
            return false;
        }

        if (('[' == xstr_name.at(0)) &&
            (std::string::npos != xstr_name.find(']')))
        {
            return false;
        }

        return true;
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_keyvalue_t 对象。
     *
     * @param [in ] xstr_line  :
     *  用于创建 键值节点 的字符串行，其已经被 trim_xstr() 修剪前后端的空白字符。
     *
     * @param [in ] xowner_ptr : 键值节点的拥有者（xini_section_t 类型）。
     *
     * @return xini_node_t * :
     *  操作成功，返回的 键值节点；若失败，则返回 NULL 。
     */
    static xini_node_t*
        try_create(
            const std::string& xstr_line,
            xini_node_t* xowner_ptr)
    {
        assert(is_xtrim(xstr_line));
        assert(is_sline(xstr_line));

        if (xstr_line.empty())
        {
            return NULL;
        }

        // 等号位置
        size_t st_eq = xstr_line.find('=');
        if ((0 == st_eq) || (std::string::npos == st_eq))
        {
            return NULL;
        }

        // 键名
        std::string xstr_kname = trim_xstr(xstr_line.substr(0, st_eq));
        if (!check_kname(xstr_kname))
        {
            return NULL;
        }

        //======================================

        xini_keyvalue_t* xnode_ptr = new xini_keyvalue_t(xowner_ptr);

        xnode_ptr->m_xstr_kname = xstr_kname;
        xnode_ptr->m_xstr_value = trim_xstr(xstr_line.substr(st_eq + 1));

        //======================================

        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_keyvalue_t(xini_node_t* xowner_ptr)
        : xini_node_t(XINI_NTYPE_KEYVALUE, xowner_ptr)
    {

    }

    virtual ~xini_keyvalue_t(void)
    {

    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const
    {
        ostr << m_xstr_kname
            << '='
            << m_xstr_value
            << std::endl;
        return *this;
    }

    // template<> functions, for operators
protected:
    /**********************************************************/
    /**
     * @brief 数值的读操作。
     */
    template< typename __number_type >
    __number_type get_numb(void) const
    {
        __number_type      numb{};
        std::istringstream istr(m_xstr_value);
        istr >> numb;
        if (istr.fail())
            return static_cast<__number_type>(0);
        return numb;
    }

    /**********************************************************/
    /**
     * @brief 数值的读操作（带默认值）。
     */
    template< typename __number_type >
    __number_type get_numb(__number_type x_default) const
    {
        if (empty())
            return x_default;

        __number_type      numb{};
        std::istringstream istr(m_xstr_value);
        istr >> numb;
        if (istr.fail())
            return x_default;
        return numb;
    }

    /**********************************************************/
    /**
     * @brief 数值的写操作。
     */
    template< typename __number_type >
    void set_numb(__number_type x_value)
    {
        std::ostringstream ostr;
        ostr << x_value;
        assert(!ostr.fail());
        invk_set_value(ostr.str());
    }

    /**********************************************************/
    /**
     * @brief 数值的写操作。
     */
    template< typename __number_type >
    void set_numb(__number_type x_value, std::streamsize x_precision)
    {
        std::ostringstream ostr;
        ostr.precision(x_precision);
        ostr << x_value;
        assert(!ostr.fail());
        invk_set_value(ostr.str());
    }

    /**********************************************************/
    /**
     * @brief 数值的读操作（键值为 空（或格式非法）时，同步写入默认值）。
     */
    template< typename __number_type >
    __number_type try_numb(__number_type x_default)
    {
        if (empty())
        {
            set_numb(x_default);
            return x_default;
        }

        __number_type      numb{};
        std::istringstream istr(m_xstr_value);
        istr >> numb;
        if (istr.fail())
        {
            set_numb(x_default);
            return x_default;
        }

        return numb;
    }

    /**********************************************************/
    /**
     * @brief 数值的读操作（键值为 空（或格式非法）时，同步写入默认值）。
     */
    template< typename __number_type >
    __number_type try_numb(__number_type x_default, std::streamsize x_precision)
    {
        if (empty())
        {
            set_numb(x_default, x_precision);
            return x_default;
        }

        __number_type      numb{};
        std::istringstream istr(m_xstr_value);
        istr >> numb;
        if (istr.fail())
        {
            set_numb(x_default, x_precision);
            return x_default;
        }

        return numb;
    }

    /**********************************************************/
    /**
     * @brief bool 值的读操作（键值为 空（或格式非法）时，同步写入默认值）。
     */
    bool try_bool(bool x_default)
    {
        //======================================
        // 按 字符串 解析

        if (empty())
        {
            invk_set_value(std::string(x_default ? "true" : "false"));
            return x_default;
        }

        if (0 == xstr_icmp(m_xstr_value.c_str(), "true"))
            return true;
        if (0 == xstr_icmp(m_xstr_value.c_str(), "false"))
            return false;

        //======================================
        // 按 整数值 解析

        long               numb;
        std::istringstream istr(m_xstr_value);
        istr >> numb;
        if (istr.fail())
        {
            invk_set_value(std::string(x_default ? "true" : "false"));
            return x_default;
        }

        invk_set_value(std::string((0L != numb) ? "true" : "false"));
        return (0L != numb);

        //======================================
    }

    // operators
public:
    //======================================
    // 基础数据类型的读操作

    operator const char* () const { return m_xstr_value.c_str(); }

    operator bool() const
    {
        if (0 == xstr_icmp(m_xstr_value.c_str(), "true"))
            return true;
        if (0 == xstr_icmp(m_xstr_value.c_str(), "false"))
            return false;
        return (0L != get_numb< long >());
    }

    operator short() const { return get_numb< short              >(); }
    operator unsigned short() const { return get_numb< unsigned short     >(); }
    operator int() const { return get_numb< int                >(); }
    operator unsigned int() const { return get_numb< unsigned int       >(); }
    operator long() const { return get_numb< long               >(); }
    operator unsigned long() const { return get_numb< unsigned long      >(); }
    operator long long() const { return get_numb< long long          >(); }
    operator unsigned long long() const { return get_numb< unsigned long long >(); }
    operator float() const { return get_numb< float              >(); }
    operator double() const { return get_numb< double             >(); }
    operator long double() const { return get_numb< long double        >(); }

    //======================================
    // 重载 operator ()，实现带上默认值的读操作

    const char* operator () (const char* x_default) const
    {
        if (empty())
            return x_default;
        return m_xstr_value.c_str();
    }

    bool operator () (bool x_default) const
    {
        if (0 == xstr_icmp(m_xstr_value.c_str(), "true"))
            return true;
        if (0 == xstr_icmp(m_xstr_value.c_str(), "false"))
            return false;
        return (0 != get_numb< int >(x_default ? 1 : 0));
    }

    short              operator () (short               x_default) const { return get_numb< short              >(x_default); }
    unsigned short     operator () (unsigned short      x_default) const { return get_numb< unsigned short     >(x_default); }
    int                operator () (int                 x_default) const { return get_numb< int                >(x_default); }
    unsigned int       operator () (unsigned int        x_default) const { return get_numb< unsigned int       >(x_default); }
    long               operator () (long                x_default) const { return get_numb< long               >(x_default); }
    unsigned long      operator () (unsigned long       x_default) const { return get_numb< unsigned long      >(x_default); }
    long long          operator () (long long           x_default) const { return get_numb< long long          >(x_default); }
    unsigned long long operator () (unsigned long long  x_default) const { return get_numb< unsigned long long >(x_default); }
    float              operator () (float               x_default) const { return get_numb< float              >(x_default); }
    double             operator () (double              x_default) const { return get_numb< double             >(x_default); }
    long double        operator () (long double         x_default) const { return get_numb< long double        >(x_default); }

    const char* operator () (const std::string& x_default) const { return this->operator ()(x_default.c_str()); }

    //======================================
    // 与重载的 operator () 带默认值读取操作符功能类似，
    // 但键值为 空（或格式非法）时，会同步写入默认值

    const char* try_value(const char* x_default)
    {
        if (empty())
            set_value(x_default);
        return m_xstr_value.c_str();
    }

    bool try_value(bool x_default)
    {
        return try_bool(x_default);
    }

    short              try_value(short               x_default) { return try_numb< short              >(x_default); }
    unsigned short     try_value(unsigned short      x_default) { return try_numb< unsigned short     >(x_default); }
    int                try_value(int                 x_default) { return try_numb< int                >(x_default); }
    unsigned int       try_value(unsigned int        x_default) { return try_numb< unsigned int       >(x_default); }
    long               try_value(long                x_default) { return try_numb< long               >(x_default); }
    unsigned long      try_value(unsigned long       x_default) { return try_numb< unsigned long      >(x_default); }
    long long          try_value(long long           x_default) { return try_numb< long long          >(x_default); }
    unsigned long long try_value(unsigned long long  x_default) { return try_numb< unsigned long long >(x_default); }
    float              try_value(float               x_default) { return try_numb< float              >(x_default, 6); }
    double             try_value(double              x_default) { return try_numb< double             >(x_default, 16); }
    long double        try_value(long double         x_default) { return try_numb< long double        >(x_default, 16); }

    const char* try_value(const std::string& x_default) { return this->try_value(x_default.c_str()); }

    //======================================
    // 基础数据类型的写操作

    xini_keyvalue_t& operator = (const char* x_value) { set_value(std::string(x_value));               return *this; }
    xini_keyvalue_t& operator = (bool               x_value) { invk_set_value(std::string(x_value ? "true" : "false")); return *this; }
    xini_keyvalue_t& operator = (short              x_value) { set_numb< short              >(x_value); return *this; }
    xini_keyvalue_t& operator = (unsigned short     x_value) { set_numb< unsigned short     >(x_value); return *this; }
    xini_keyvalue_t& operator = (int                x_value) { set_numb< int                >(x_value); return *this; }
    xini_keyvalue_t& operator = (unsigned int       x_value) { set_numb< unsigned int       >(x_value); return *this; }
    xini_keyvalue_t& operator = (long               x_value) { set_numb< long               >(x_value); return *this; }
    xini_keyvalue_t& operator = (unsigned long      x_value) { set_numb< unsigned long      >(x_value); return *this; }
    xini_keyvalue_t& operator = (long long          x_value) { set_numb< long long          >(x_value); return *this; }
    xini_keyvalue_t& operator = (unsigned long long x_value) { set_numb< unsigned long long >(x_value); return *this; }
    xini_keyvalue_t& operator = (float              x_value) { set_numb< float              >(x_value, 6); return *this; }
    xini_keyvalue_t& operator = (double             x_value) { set_numb< double             >(x_value, 16); return *this; }
    xini_keyvalue_t& operator = (long double        x_value) { set_numb< long double        >(x_value, 16); return *this; }

    xini_keyvalue_t& operator = (const std::string& x_value) { set_value(x_value); return *this; }

    /**********************************************************/
    /**
     * @brief 键值节点相互赋值时，只 取值 而 忽略 键名。
     */
    xini_keyvalue_t& operator = (const xini_keyvalue_t& x_value)
    {
        if (this != &x_value)
            invk_set_value(x_value.value());
        return *this;
    }

    //======================================

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 键名。
     */
    inline const std::string& key(void) const
    {
        return m_xstr_kname;
    }

    /**********************************************************/
    /**
     * @brief 键值。
     */
    inline const std::string& value(void) const
    {
        return m_xstr_value;
    }

    /**********************************************************/
    /**
     * @brief 判断 键值 是否为 空。
     */
    inline bool empty(void) const
    {
        return m_xstr_value.empty();
    }

    /**********************************************************/
    /**
     * @brief 修改键名。
     */
    bool set_key(const std::string& xstr_key)
    {
        std::string xstr_kname = trim_xstr(xstr_key);
        if (check_kname(xstr_kname))
        {
            return false;
        }

        return get_owner()->rename_nsub(this, xstr_kname);
    }

    /**********************************************************/
    /**
     * @brief 设置键值。
     */
    inline void set_value(const std::string& x_value)
    {
        std::string xstr = x_value.substr(0, x_value.find_first_of("\r\n"));
        invk_set_value(trim_xstr(xstr));
    }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 设置（单行文本 且 去除头尾空白字符 的）键值。
     */
    inline void invk_set_value(const std::string& xstr_value)
    {
        if (xstr_value != m_xstr_value)
        {
            m_xstr_value = xstr_value;
            set_dirty(true);
        }
    }

protected:
    std::string   m_xstr_kname;  ///< 键名
    std::string   m_xstr_value;  ///< 键值
};

////////////////////////////////////////////////////////////////////////////////
// xini_section_t

/**
 * @class xini_section_t
 * @brief INI 文件中的 分节 节点类。
 */
class xini_section_t : public xini_node_t
{
    friend class xini_file_t;
    friend class xini_keyvalue_t;

    // common data types
protected:
    typedef std::list< xini_node_t* >                              xlst_node_t;
    typedef std::map< std::string, xini_keyvalue_t*, xstr_icmp_t > xmap_ndkv_t;
public:
    typedef xlst_node_t::iterator       iterator;
    typedef xlst_node_t::const_iterator const_iterator;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 修剪 分节名字符串 前后端多余的字符。
     */
    static inline std::string trim_sname(const std::string& xstr_name)
    {
        return trim_xstr(xstr_name, "[] \t\n\r\f\v");
    }

    /**********************************************************/
    /**
     * @brief 检查分节名字符串格式是否有效。
     *
     * @param [in ] xstr_name :
     *  待检查的 分节名，操作前其已经被
     *  trim_sname() 修剪过前后端多余的字符。
     */
    static inline bool check_sname(const std::string& xstr_name)
    {
        assert(is_xtrim(xstr_name));
        return is_sline(xstr_name);
    }

    /**********************************************************/
    /**
     * @brief 尝试使用字符串直接创建并初始化 xini_section_t 对象。
     */
    static xini_node_t*
        try_create(
            const std::string& xstr_line,
            xini_node_t* xowner_ptr)
    {
        assert(is_xtrim(xstr_line));
        assert(is_sline(xstr_line));

        //======================================

        if (xstr_line.empty())
        {
            return NULL;
        }

        if ('[' != xstr_line.at(0))
        {
            return NULL;
        }

        std::string::size_type st_pos = xstr_line.find(']', 1);
        if (std::string::npos == st_pos)
        {
            return NULL;
        }

        //======================================

        xini_section_t* xnode_ptr = new xini_section_t(xowner_ptr);
        xnode_ptr->m_xstr_name = trim_xstr(xstr_line.substr(1, st_pos - 1));

        // 将 自身 作为 节点 加入到 m_xlst_node 中，但并不意味着 m_xlst_node 
        // 的 首个节点 就一定是 自身节点，因为 xini_file_t 在加载过程中，
        // 会调用 pop_tail_comment() 操作，这有可能在 m_xlst_node 前端新增
        // 一些 注释/空行节点。所以在进行 流输出 操作时，自身节点 则可起到 占位行
        // 的作用，详细过程可参看 operator >> 的实现流程
        xnode_ptr->m_xlst_node.push_back(xnode_ptr);

        return xnode_ptr;
    }

    // construcor/destructor
protected:
    xini_section_t(xini_node_t* xowner_ptr)
        : xini_node_t(XINI_NTYPE_SECTION, xowner_ptr)
    {

    }

    virtual ~xini_section_t(void)
    {
        for (std::list< xini_node_t* >::iterator
            itlst = m_xlst_node.begin();
            itlst != m_xlst_node.end();
            ++itlst)
        {
            if (XINI_NTYPE_SECTION != (*itlst)->ntype())
            {
                delete (*itlst);
            }
        }

        m_xlst_node.clear();
        m_xmap_ndkv.clear();
    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const
    {
        for (std::list< xini_node_t* >::const_iterator
            itlst = m_xlst_node.begin();
            itlst != m_xlst_node.end();
            ++itlst)
        {
            if (this == static_cast<xini_section_t*>(
                const_cast<xini_node_t*>(*itlst)))
            {
                if (!m_xstr_name.empty())
                {
                    ostr << "[" << m_xstr_name << "]" << std::endl;
                }
            }
            else
            {
                **itlst >> ostr;
            }
        }

        return *this;
    }

protected:
    /**********************************************************/
    /**
     * @brief 重命名附属的子节点（键值节点）的索引名。
     * @note  该接口仅由 xini_keyvalue_t::set_key() 调用。
     */
    virtual bool rename_nsub(
        xini_node_t* xnsub_ptr,
        const std::string& xstr_name)
    {
        assert(XINI_NTYPE_KEYVALUE == xnsub_ptr->ntype());

        return rename_knode(
            static_cast<xini_keyvalue_t*>(xnsub_ptr), xstr_name);
    }

    // overrides : operator
public:
    /**********************************************************/
    /**
     * @brief 重载 operator [] 操作符，实现 键值 节点的索引操作。
     */
    xini_keyvalue_t& operator [] (const std::string& xstr_key)
    {
        //======================================

        std::string xstr_nkey = trim_xstr(xstr_key);
        assert(xini_keyvalue_t::check_kname(xstr_nkey));

        //======================================

        xini_keyvalue_t* xndkv_ptr = find_knode(xstr_nkey);
        if (NULL != xndkv_ptr)
        {
            return *xndkv_ptr;
        }

        //======================================
        // 若索引的 键值节点 并未在节点表中，
        // 则 新增 此 键值节点，但并不设置 脏标识，
        // 避免存储不必要的 空键值节点

        xndkv_ptr =
            static_cast<xini_keyvalue_t*>(
                xini_keyvalue_t::try_create(xstr_nkey + "=", get_owner()));
        assert(NULL != xndkv_ptr);

        m_xlst_node.push_back(xndkv_ptr);
        m_xmap_ndkv.insert(std::make_pair(xstr_nkey, xndkv_ptr));

        //======================================

        return *xndkv_ptr;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 分节 名称。
     */
    inline const std::string& name(void) const
    {
        return m_xstr_name;
    }

    /**********************************************************/
    /**
     * @brief 修改 分节 名称。
     */
    bool set_name(const std::string& xstr_name)
    {
        std::string xstr_sname = trim_sname(xstr_name);
        if (!check_sname(xstr_sname))
        {
            return false;
        }

        return get_owner()->rename_nsub(this, xstr_sname);
    }

    /**********************************************************/
    /**
     * @brief 分节 内的节点数量。
     */
    inline size_t size(void) const
    {
        return m_xlst_node.size();
    }

    /**********************************************************/
    /**
     * @brief 分节 是否为空。
     */
    inline bool empty() const
    {
        return m_xlst_node.empty();
    }

    /**********************************************************/
    /**
     * @brief 判断当前分节是否以空行结尾。
     */
    inline bool has_end_nilline(void) const
    {
        if (!m_xlst_node.empty() &&
            (XINI_NTYPE_NILLINE == m_xlst_node.back()->ntype()))
        {
            return true;
        }
        return false;
    }

    /**********************************************************/
    /**
     * @brief 判定当前是否已经包含指定的 键值节点。
     */
    inline bool key_included(const std::string& xstr_key) const
    {
        return (NULL != find_knode(trim_xstr(xstr_key)));
    }

    /**********************************************************/
    /**
     * @brief 对 键值节点 进行重命名（索引键名）操作。
     *
     * @param [in ] xstr_key  : 目标操作的索引键名。
     * @param [in ] xstr_name : 重新设置键值节点的索引键名。
     *
     * @return 重命名操作 是否成功。
     */
    bool key_rename(const std::string& xstr_key, const std::string& xstr_name)
    {
        //======================================

        xini_keyvalue_t* xndkv_ptr = find_knode(trim_xstr(xstr_key));
        if (NULL == xndkv_ptr)
        {
            return false;
        }

        //======================================

        std::string xstr_kname = trim_xstr(xstr_name);
        if (!xini_keyvalue_t::check_kname(xstr_kname))
        {
            return false;
        }

        return rename_knode(xndkv_ptr, xstr_kname);
    }

    /**********************************************************/
    /**
     * @brief 删除指定键值。
     */
    bool key_remove(const std::string& xstr_key)
    {
        //======================================

        xmap_ndkv_t::iterator itmap = m_xmap_ndkv.find(trim_xstr(xstr_key));
        if (itmap == m_xmap_ndkv.end())
        {
            return false;
        }

        //======================================

        for (xlst_node_t::iterator
            itlst = m_xlst_node.begin();
            itlst != m_xlst_node.end();
            ++itlst)
        {
            if (XINI_NTYPE_KEYVALUE != (*itlst)->ntype())
                continue;

            if (static_cast<xini_node_t*>(itmap->second) == (*itlst))
            {
                delete* itlst;
                m_xlst_node.erase(itlst);

                break;
            }
        }

        m_xmap_ndkv.erase(itmap);

        set_dirty(true);

        //======================================

        return true;
    }

    // iterator
public:
    /**********************************************************/
    /**
     * @brief 节点表的起始位置迭代器。
     */
    inline iterator begin(void) { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief 节点表的起始位置迭代器。
     */
    inline const_iterator begin(void) const { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief 节点表的结束位置迭代器。
     */
    inline iterator end(void) { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief 节点表的结束位置迭代器。
     */
    inline const_iterator end(void) const { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief 返回节点表中 首个 键值节点 的迭代器。
     */
    inline iterator begin_kv(void)
    {
        iterator xiter = m_xlst_node.begin();
        if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
            return xiter;
        return next_kv(xiter);
    }

    /**********************************************************/
    /**
     * @brief 返回节点表中 首个 键值节点 的迭代器。
     */
    inline const_iterator begin_kv(void) const
    {
        const_iterator xiter = m_xlst_node.begin();
        if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
            return xiter;
        return next_kv(xiter);
    }

    /**********************************************************/
    /**
     * @brief 返回 下一个 键值节点 的迭代器。
     */
    iterator next_kv(iterator xiter)
    {
        const iterator xiter_end = m_xlst_node.end();
        if (xiter != xiter_end)
        {
            while (++xiter != xiter_end)
                if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
                    return xiter;
        }

        return xiter_end;
    }

    /**********************************************************/
    /**
     * @brief 返回 下一个 键值节点 的迭代器。
     */
    const_iterator next_kv(const_iterator xiter) const
    {
        const const_iterator xiter_end = m_xlst_node.end();
        if (xiter != xiter_end)
        {
            while (++xiter != xiter_end)
                if (XINI_NTYPE_KEYVALUE == (*xiter)->ntype())
                    return xiter;
        }

        return xiter_end;
    }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 添加（空行、注释、键值 类型的）节点。
     *
     * @param [in ] xnode_ptr: （空行、注释、键值 类型的）节点。
     *
     * @return 操作是否成功。
     */
    bool push_node(xini_node_t* xnode_ptr)
    {
        if (NULL == xnode_ptr)
        {
            return false;
        }

        if ((XINI_NTYPE_NILLINE == xnode_ptr->ntype()) ||
            (XINI_NTYPE_COMMENT == xnode_ptr->ntype()))
        {
            m_xlst_node.push_back(xnode_ptr);
            return true;
        }

        if (XINI_NTYPE_KEYVALUE == xnode_ptr->ntype())
        {
            xini_keyvalue_t* xnode_kvptr =
                static_cast<xini_keyvalue_t*>(xnode_ptr);

            if (NULL != find_knode(xnode_kvptr->key()))
            {
                return false;
            }

            m_xlst_node.push_back(xnode_ptr);
            m_xmap_ndkv.insert(std::make_pair(xnode_kvptr->key(), xnode_kvptr));
            return true;
        }

        return false;
    }

    /**********************************************************/
    /**
     * @brief 查找分节下的 键值 节点。
     *
     * @param [in ] xstr_xkey: 索引键字符串，比较时忽略大小写。
     *
     * @return xini_keyvalue_t *
     *         - 成功，返回 对应的节点；
     *         - 失败，返回 NULL 。
     */
    xini_keyvalue_t* find_knode(const std::string& xstr_xkey) const
    {
        xmap_ndkv_t::const_iterator itfind = m_xmap_ndkv.find(xstr_xkey);
        if (itfind != m_xmap_ndkv.end())
        {
            return itfind->second;
        }

        return NULL;
    }

    /**********************************************************/
    /**
     * @brief 从 节点表 尾部取出 非当前 分节 下的注释节点（按 空行 节点作为分界）。
     *
     * @param [in ] xlst_comm : 接收返回的注释节点表（在链表头部添加返回的节点）。
     * @param [in ] xbt_front : 表明操作是从 xlst_comm 前/后附加返回的节点。
     *
     * @return size_t
     *         - 返回取出的节点数量。
     */
    size_t pop_tail_comment(std::list< xini_node_t* >& xlst_comm, bool xbt_front)
    {
        std::list< xini_node_t* > xlst_node;

        size_t xst_line = 0;
        size_t xst_maxl = m_xlst_node.size();

        // 节点表只有三种类型的节点：键值，空行，注释，
        // 以及 另外加上 自身的 分节节点

        while ((xst_line++ < xst_maxl) && !m_xlst_node.empty())
        {
            xini_node_t* xnode_ptr = m_xlst_node.back();

            // 遇到空行节点
            if (XINI_NTYPE_NILLINE == xnode_ptr->ntype())
            {
                if (xst_line > 1)
                    break;

                // 只容许第一个是空行
                xlst_node.push_front(xnode_ptr);
                m_xlst_node.pop_back();
                continue;
            }

            // 若反向遍历过程中，一直未遇到空行，
            // 则将原取出的注释节点还回节点表中
            if ((XINI_NTYPE_KEYVALUE == xnode_ptr->ntype()) ||
                (XINI_NTYPE_SECTION == xnode_ptr->ntype()))
            {
                m_xlst_node.splice(m_xlst_node.end(), xlst_node);
                break;
            }

            if (XINI_NTYPE_COMMENT == xnode_ptr->ntype())
            {
                xlst_node.push_front(xnode_ptr);
                m_xlst_node.pop_back();
            }
            else
            {
                // 未识别的节点类型
                assert(false);
            }
        }

        size_t xst_count = xlst_node.size();
        if (xst_count > 0)
        {
            // 设置返回结果
            if (xbt_front)
            {
                xlst_node.splice(xlst_node.end(), xlst_comm);
                xlst_comm.swap(xlst_node);
            }
            else
            {
                xlst_comm.splice(xlst_comm.end(), xlst_node);
            }
        }

        return xst_count;
    }

    /**********************************************************/
    /**
     * @brief 对 键值节点 进行重命名操作。
     *
     * @param [in ] xndkv_ptr : 目标操作的键值节点。
     * @param [in ] xstr_name : 重新设置键值节点的索引键名。
     *
     * @return 重命名操作 是否成功。
     */
    bool rename_knode(xini_keyvalue_t* xndkv_ptr, const std::string& xstr_name)
    {
        //======================================

        // 与键值节点原有名称一致，忽略后续操作
        if (0 == xstr_icmp(xndkv_ptr->key().c_str(), xstr_name.c_str()))
        {
            return true;
        }

        // 判定所要设置的键值节点名称，
        // 与节点表中的其他键值节点名称 是否重名
        if (NULL != find_knode(xstr_name))
        {
            return false;
        }

        //======================================
        // 先从映射表中移除旧有的键值节点映射，
        // 再对键值节点进行重命名，最后重新加入到映射表中

        m_xmap_ndkv.erase(xndkv_ptr->key());
        xndkv_ptr->m_xstr_kname = xstr_name;
        m_xmap_ndkv.insert(std::make_pair(xndkv_ptr->key(), xndkv_ptr));

        set_dirty(true);

        //======================================

        return true;
    }

protected:
    std::string   m_xstr_name;  ///< 分节名称
    xlst_node_t   m_xlst_node;  ///< 分节下的节点表
    xmap_ndkv_t   m_xmap_ndkv;  ///< 分节下的 键值节点 映射表
};

////////////////////////////////////////////////////////////////////////////////
// xini_file_t

/**
 * @class xini_file_t
 * @brief INI 文件操作类。
 */
class xini_file_t : public xini_node_t
{
    friend class xini_section_t;

    // common data types
protected:
    typedef std::list< xini_section_t* >                          xlst_section_t;
    typedef std::map< std::string, xini_section_t*, xstr_icmp_t > xmap_section_t;
public:
    typedef xlst_section_t::iterator       iterator;
    typedef xlst_section_t::const_iterator const_iterator;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief 依据给定的 INI 文本行，创建相应的节点。
     */
    static xini_node_t*
        make_node(
            const std::string& xstr_line,
            xini_file_t* xowner_ptr)
    {
        xini_node_t* xnode_ptr = NULL;

#define XTRY_CREATE(nptr, node, owner)                 \
        do                                             \
        {                                              \
            nptr = node::try_create(xstr_line, owner); \
            if (NULL != nptr)                          \
                return nptr;                           \
        } while (0)

        XTRY_CREATE(xnode_ptr, xini_nilline_t, xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_comment_t, xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_section_t, xowner_ptr);
        XTRY_CREATE(xnode_ptr, xini_keyvalue_t, xowner_ptr);

#undef XTRY_CREATE

        return xnode_ptr;
    }

    // constructor/destructor
public:
    xini_file_t(void)
        : xini_node_t(XINI_NTYPE_FILEROOT, NULL)
        , m_xbt_dirty(false)
    {

    }

    xini_file_t(const std::string& xstr_filepath)
        : xini_node_t(XINI_NTYPE_FILEROOT, NULL)
        , m_xbt_dirty(false)
    {
        load(xstr_filepath);
    }

    virtual ~xini_file_t(void)
    {
        release();
    }

    // overrides
public:
    /**********************************************************/
    /**
     * @brief 将 节点信息 导向 输出流。
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const
    {
        for (std::list< xini_section_t* >::const_iterator
            itlst = m_xlst_sect.begin();
            itlst != m_xlst_sect.end();
            ++itlst)
        {
            if ((*itlst)->empty())
                continue;

            **itlst >> ostr;
            if (!(*itlst)->has_end_nilline() &&
                ((*itlst) != m_xlst_sect.back()))
            {
                ostr << std::endl;
            }
        }

        return *this;
    }

    /**********************************************************/
    /**
     * @brief 脏标识。
     */
    virtual bool is_dirty(void) const
    {
        return m_xbt_dirty;
    }

    /**********************************************************/
    /**
     * @brief 设置脏标识。
     */
    virtual void set_dirty(bool x_dirty)
    {
        m_xbt_dirty = x_dirty;
    }

protected:
    /**********************************************************/
    /**
     * @brief 重命名附属的子节点（分节节点）的索引名。
     * @note  该接口仅由 xini_section_t::set_name() 调用。
     */
    virtual bool rename_nsub(
        xini_node_t* xnsub_ptr,
        const std::string& xstr_name)
    {
        assert(XINI_NTYPE_SECTION == xnsub_ptr->ntype());

        return rename_sect(
            static_cast<xini_section_t*>(xnsub_ptr), xstr_name);
    }

    // overrides : operator
public:
    /**********************************************************/
    /**
     * @brief 从 输出流 构建 xini_file_t 内容。
     */
    xini_file_t& operator << (std::istream& istr)
    {
        //======================================

        // 记录当前操作的分节
        xini_section_t* xsect_ptr = NULL;

        if (m_xlst_sect.empty())
        {
            // 当前分节表为空，则创建一个空分节名的 分节 节点
            xsect_ptr = new xini_section_t(this);
            m_xlst_sect.push_back(xsect_ptr);

            assert(m_xmap_sect.empty());
            m_xmap_sect.insert(std::make_pair(std::string(""), xsect_ptr));
        }
        else
        {
            // 取尾部分节作为当前操作的 分节 节点
            xsect_ptr = m_xlst_sect.back();

            // 确保尾部分节空行结尾
            if (!xsect_ptr->has_end_nilline())
            {
                xsect_ptr->push_node(new xini_nilline_t(this));
            }
        }

        //======================================

        // 逐行解析 INI 文件，构建节点表
        while (!istr.eof())
        {
            //======================================
            // 读取文本行

            std::string xstr_line;
            std::getline(istr, xstr_line);
            xstr_line = trim_xstr(xstr_line);

            // 最后一个空行不放到节点表中，避免文件关闭时 持续增加 尾部空行
            if (istr.eof() && xstr_line.empty())
            {
                break;
            }

            //======================================

            // 创建节点
            xini_node_t* xnode_ptr = make_node(xstr_line, this);
            if (NULL == xnode_ptr)
            {
                continue;
            }

            // 若为 分节 节点，则加入到分节表中，并更新当前操作的 分节节点
            if (XINI_NTYPE_SECTION == xnode_ptr->ntype())
            {
                xsect_ptr =
                    push_sect(static_cast<xini_section_t*>(xnode_ptr),
                        xsect_ptr);

                if (xsect_ptr != static_cast<xini_section_t*>(xnode_ptr))
                    delete xnode_ptr; // 添加新分节失败，删除该节点
                else
                    set_dirty(true);  // 添加新分节成功，设置脏标识

                continue;
            }

            // 加入 当前分节
            if (xsect_ptr->push_node(xnode_ptr))
            {
                set_dirty(true);
            }
            else
            {
                // 加入分节失败，可能是因为：
                // 其为 键值 节点，与 分节 节点表中已有的 节点 索引键 冲突
                delete xnode_ptr;
            }

            //======================================
        }

        //======================================

        return *this;
    }

    /**********************************************************/
    /**
     * @brief 重载 operator [] 操作符，实现 分节 索引操作。
     */
    xini_section_t& operator [] (const std::string& xstr_sect)
    {
        //======================================

        std::string xstr_name = xini_section_t::trim_sname(xstr_sect);
        assert(xini_section_t::check_sname(xstr_name));

        //======================================

        xini_section_t* xsect_ptr = find_sect(xstr_name);
        if (NULL != xsect_ptr)
        {
            return *xsect_ptr;
        }

        //======================================
        // 若索引的分节并未在 分节 的节点表中，
        // 则 新增 此分节，但并不设置 脏标识，
        // 避免存储不必要的  空分节

        xsect_ptr =
            static_cast<xini_section_t*>(
                xini_section_t::try_create("[" + xstr_name + "]", this));
        assert(NULL != xsect_ptr);

        m_xlst_sect.push_back(xsect_ptr);
        m_xmap_sect.insert(std::make_pair(xstr_name, xsect_ptr));

        //======================================

        return *xsect_ptr;
    }

    // public interfaces
public:
    /**********************************************************/
    /**
     * @brief 从指定路径的文件中加载 INI 内容。
     * @note
     *  load() 操作的成功与否，并不影响后续的键值读写操作，
     *  其只能标示 xini_file_t 对象是否关联可至指定路径
     *  （本地磁盘 或 远程网络 等的）文件。
     *
     * @param [in ] xstr_text : 文件路径。
     *
     * @return bool
     *         - 成功，返回 true ；
     *         - 失败，返回 false。
     */
    bool load(const std::string& xstr_filepath)
    {
        // 先释放当前对象
        release();

        // 不管后续操作是否成功，都关联到新指定的 INI 文件路径
        m_xstr_path = xstr_filepath;

        if (xstr_filepath.empty())
        {
            return false;
        }

        // 打开文件
        std::ifstream xfile_reader(xstr_filepath.c_str());
        if (!xfile_reader.is_open())
        {
            return false;
        }

        // 跳过字符流的头部编码信息（如 utf-8 的 bom 标识）
        while (!xfile_reader.eof())
        {
            int xchar = xfile_reader.get();
            if (std::iscntrl(xchar) || std::isprint(xchar))
            {
                xfile_reader.putback(static_cast<char>(xchar));
                break;
            }

            m_xstr_head.push_back(static_cast<char>(xchar));
        }

        *this << xfile_reader;
        set_dirty(false);

        return true;
    }

    /**********************************************************/
    /**
     * @brief 将当前文件根下的所有节点直接输出到文件中。
     */
    bool dump(const std::string& xstr_filepath)
    {
        // 打开文件
        std::ofstream xfile_writer(
            xstr_filepath.c_str(), std::ios_base::trunc);
        if (!xfile_writer.is_open())
        {
            return false;
        }

        if (!m_xstr_head.empty())
            xfile_writer << m_xstr_head.c_str();
        *this >> xfile_writer;

        return true;
    }

    /**********************************************************/
    /**
     * @brief 释放对象资源（可以不显示调用，对象析构函数中会自动调用该接口）。
     */
    void release(void)
    {
        if (is_dirty())
        {
            dump(m_xstr_path);
            set_dirty(false);
        }
        m_xstr_path.clear();
        m_xstr_head.clear();

        for (std::list< xini_section_t* >::iterator
            itlst = m_xlst_sect.begin();
            itlst != m_xlst_sect.end();
            ++itlst)
        {
            delete* itlst;
        }

        m_xlst_sect.clear();
        m_xmap_sect.clear();
    }

    /**********************************************************/
    /**
     * @brief 当前关联的文件路径。
     */
    inline const std::string& filepath(void) const
    {
        return m_xstr_path;
    }

    /**********************************************************/
    /**
     * @brief 返回当前分节数量。
     */
    inline size_t sect_count(void) const
    {
        return m_xlst_sect.size();
    }

    /**********************************************************/
    /**
     * @brief 判定当前是否包含指定的 分节。
     */
    inline bool sect_included(const std::string& xstr_sect) const
    {
        return (NULL != find_sect(xini_section_t::trim_sname(xstr_sect)));
    }

    /**********************************************************/
    /**
     * @brief 对 分节 进行重命名操作。
     *
     * @param [in ] xstr_sect : 目标操作的分节名称。
     * @param [in ] xstr_name : 重新设置分节的名称。
     *
     * @return 重命名操作 是否成功。
     */
    bool sect_rename(
        const std::string& xstr_sect,
        const std::string& xstr_name)
    {
        //======================================

        xini_section_t* xsect_ptr =
            find_sect(xini_section_t::trim_sname(xstr_sect));
        if (NULL == xsect_ptr)
        {
            return false;
        }

        //======================================

        std::string xstr_sname = xini_section_t::trim_sname(xstr_name);
        if (!xini_section_t::check_sname(xstr_sname))
        {
            return false;
        }

        return rename_sect(xsect_ptr, xstr_sname);
    }

    /**********************************************************/
    /**
     * @brief 删除指定分节。
     */
    bool sect_remove(const std::string& xstr_sect)
    {
        //======================================

        xmap_section_t::iterator itmap =
            m_xmap_sect.find(xini_section_t::trim_sname(xstr_sect));
        if (itmap == m_xmap_sect.end())
        {
            return false;
        }

        //======================================

        for (xlst_section_t::iterator
            itlst = m_xlst_sect.begin();
            itlst != m_xlst_sect.end();
            ++itlst)
        {
            if (itmap->second == (*itlst))
            {
                delete* itlst;
                m_xlst_sect.erase(itlst);

                break;
            }
        }

        m_xmap_sect.erase(itmap);

        set_dirty(true);

        //======================================

        return true;
    }

    // iterator
public:
    /**********************************************************/
    /**
     * @brief 分节表的起始位置迭代器。
     */
    inline iterator begin(void) { return m_xlst_sect.begin(); }

    /**********************************************************/
    /**
     * @brief 分节表的起始位置迭代器。
     */
    inline const_iterator begin(void) const { return m_xlst_sect.begin(); }

    /**********************************************************/
    /**
     * @brief 分节表的结束位置迭代器。
     */
    inline iterator end(void) { return m_xlst_sect.end(); }

    /**********************************************************/
    /**
     * @brief 分节表的结束位置迭代器。
     */
    inline const_iterator end(void) const { return m_xlst_sect.end(); }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief 查找分节。
     */
    xini_section_t* find_sect(const std::string& xstr_sect) const
    {
        xmap_section_t::const_iterator itfind = m_xmap_sect.find(xstr_sect);
        if (itfind != m_xmap_sect.end())
        {
            return itfind->second;
        }

        return NULL;
    }

    /**********************************************************/
    /**
     * @brief 加入新分节（该接口仅由 operator << 调用）。
     *
     * @param [in ] xnew_ptr  : 新增分节。
     * @param [in ] xsect_ptr : 当前操作分节。
     *
     * @return xini_section_t *
     *         - 返回当前操作分节。
     *         - 若返回值 != xnew_ptr 则表示操作失败，新增分节和内部分节重名。
     */
    xini_section_t* push_sect(xini_section_t* xnew_ptr,
        xini_section_t* xsect_ptr)
    {
        // 查找同名分节
        xini_section_t* xfind_ptr = find_sect(xnew_ptr->name());

        if (NULL == xfind_ptr)
        {
            // 不存在同名分节，则将新增分节加入到节点表尾部
            m_xlst_sect.push_back(xnew_ptr);
            m_xmap_sect.insert(std::make_pair(xnew_ptr->name(), xnew_ptr));

            // 将当前操作分节的节点表中的 尾部注释节点，
            // 全部转移到新增分节的节点表前
            xsect_ptr->pop_tail_comment(xnew_ptr->m_xlst_node, true);

            // 将新增分节作为当前操作分节返回
            xsect_ptr = xnew_ptr;
        }
        else if (xfind_ptr != xsect_ptr)
        {
            // 将当前操作分节的节点表中的 尾部注释节点，
            // 全部转移到同名分节的节点表后

            // 保证空行隔开
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));
            }

            // 增加注释节点
            xsect_ptr->pop_tail_comment(xfind_ptr->m_xlst_node, false);

            // 保证空行隔开
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));
            }

            // 将同名分节作为当前操作分节返回
            xsect_ptr = xfind_ptr;
        }

        return xsect_ptr;
    }

    /**********************************************************/
    /**
     * @brief 对 分节 进行重命名操作。
     *
     * @param [in ] xsect_ptr : 目标操作的分节。
     * @param [in ] xstr_name : 重新设置分节的名称。
     *
     * @return 重命名操作 是否成功。
     */
    bool rename_sect(xini_section_t* xsect_ptr, const std::string& xstr_name)
    {
        //======================================

        // 与分节原有名称一致，忽略后续操作
        if (0 == xstr_icmp(xsect_ptr->name().c_str(), xstr_name.c_str()))
        {
            return true;
        }

        // 判定所要设置的分节名称，
        // 与分节表中的其他分节名称 是否重名
        if (NULL != find_sect(xstr_name))
        {
            return false;
        }

        //======================================
        // 先从映射表中移除旧有的分节节点映射，
        // 再对分节进行重命名，最后重新加入到映射表中

        m_xmap_sect.erase(xsect_ptr->name());
        xsect_ptr->m_xstr_name = xstr_name;
        m_xmap_sect.insert(std::make_pair(xsect_ptr->name(), xsect_ptr));

        set_dirty(true);

        //======================================

        return true;
    }

    // data members
protected:
    bool              m_xbt_dirty;  ///< 脏标识
    std::string       m_xstr_path;  ///< 文件路径
    std::string       m_xstr_head;  ///< 用于存储文件头的编码字符信息（如 utf-8 的 bom 标识）
    xlst_section_t    m_xlst_sect;  ///< 文件根下的 分节 节点表
    xmap_section_t    m_xmap_sect;  ///< 各个 分节 的节点映射表
};

/**********************************************************/
/**
 * @brief 定义 xini_file_t 的流输入操作符函数。
 */
inline std::istream& operator >> (
    std::istream& istr, xini_file_t& xini_file)
{
    xini_file << istr;
    return istr;
}

////////////////////////////////////////////////////////////////////////////////

#endif // __XINI_FILE_H__
