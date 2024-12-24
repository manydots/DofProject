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
  * @author  ��Gaaagaa
  * @date    : 2021-01-09
  * @version : 1.2.0.1
  * @brief   : `this->operator __base_type()`, gcc not supported.
  * @note    : Sepecial thanks for (qinwanlin)[https://gitee.com/qinwanlin].
  *
  * @author  ��Gaaagaa
  * @date    : 2020-11-07
  * @version : 1.2.0.0
  * @brief   : Improved retrieval performance of the operator[].
  *
  * @author  ��Gaaagaa
  * @date    : 2020-10-28
  * @version : 1.1.0.0
  * @brief   : update load()/release(), add operator()/try_value().
  *
  * @author  ��Gaaagaa
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
  // xini_node_t : INI �ڵ�ĳ�����

  /**
   * <pre>
   * INI �ļ���ʽ�Ľṹ���£�
   * [�ļ���]
   *     |--[����]
   *     |--[ע��]
   *     +--[�ֽ�]
   *         |--[����]
   *         |--[ע��]
   *         |--[��ֵ]
   *         |--[��ֵ]
   *         |--[����]
   *         |--[����]
   *         |--[...]
   *     |--[����]
   *     |--[����]
   *     |--[����]
   *     +--[�ֽ�]
   *           |--[����]
   *           |--[ע��]
   *           |--[��ֵ]
   *           |--[����]
   *           |--[��ֵ]
   *           |--[��ֵ]
   *           |--[��ֵ]
   *           |--[����]
   *           |--[...]
   *     |--[����]
   *     |--[...]
   *
   * �ļ�����INI �ļ����������ƣ����������ļ������С�
   * ���У��հ��У������пհ��ַ�ռ�ݣ�Ҳ��հ��С�
   * ע�ͣ��� ��;�� ���� ��#�� ��ͷ������ݣ�������ע�����ݡ�
   * �ֽڣ���ʽΪ ��[section]�� ��
   * ��ֵ����ʽΪ ��key=value�� ��
   * </pre>
   */

   /**
    * @enum  xini_node_type_t
    * @brief INI �ļ��еĽڵ���Ϣ���͡�
    */
typedef enum xini_ntype_t
{
    XINI_NTYPE_UNDEFINE = 0xFFFFFFFF, ///< δ����
    XINI_NTYPE_FILEROOT = 0x00000000, ///< �ļ���
    XINI_NTYPE_NILLINE = 0x00000100, ///< ����
    XINI_NTYPE_COMMENT = 0x00000200, ///< ע��
    XINI_NTYPE_SECTION = 0x00000300, ///< �ֽ�
    XINI_NTYPE_KEYVALUE = 0x00000400, ///< ��ֵ
} xini_ntype_t;

/** ǰ��������ص� INI �ڵ��� */
class xini_keyvalue_t;
class xini_section_t;
class xini_comment_t;
class xini_nilline_t;
class xini_file_t;

/** �ַ����޼�������Ĭ���ַ������հ��ַ������� isspace() �жϵ��ַ�Ϊ��׼�� */
static const char XCHARS_TRIM[] = " \t\n\r\f\v";

/**
 * @class xini_node_t
 * @brief INI �ڵ��������ࡣ
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
     * @brief �ж��Ƿ�Ϊ�����ַ�����
     */
    static inline bool is_sline(const std::string& xstr)
    {
        return (xstr.find_first_of("\r\n") == std::string::npos);
    }

    /**********************************************************/
    /**
     * @brief �ж��ַ����Ƿ��޼�����
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
     * @brief �޼��ַ���ǰ��˵��ַ�����
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
     * @brief �޼��ַ���ǰ�˵��ַ�����
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
     * @brief �޼��ַ�����˵��ַ�����
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
     * @brief �ַ������Դ�Сд�ıȶԲ�����
     *
     * @param [in ] xszt_lcmp : �Ƚϲ�������ֵ�ַ�����
     * @param [in ] xszt_rcmp : �Ƚϲ�������ֵ�ַ�����
     *
     * @return int
     *         - xszt_lcmp <  xszt_rcmp������ <= -1��
     *         - xszt_lcmp == xszt_rcmp������ ==  0��
     *         - xszt_lcmp >  xszt_rcmp������ >=  1��
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
     * @brief �� �ڵ���Ϣ ���� ������������������б���ʵ�־��������
     */
    virtual const xini_node_t& operator >> (std::ostream& ostr) const = 0;

    /**********************************************************/
    /**
     * @brief ���ʶ��
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
     * @brief �������ʶ��
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
     * @brief �������������ӽڵ㣨�ֽڽڵ㡢��ֵ�ڵ㣩����������
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
     * @brief �ڵ����͡�
     */
    inline int ntype(void) const { return m_xini_ntype; }

    /**********************************************************/
    /**
     * @brief ��ȡ�ڵ�ĳ����ߡ�
     */
    inline xini_node_t* get_owner(void) const { return m_xowner_ptr; }

    // data members
protected:
    int           m_xini_ntype;   ///< �ڵ�����
    xini_node_t* m_xowner_ptr;   ///< �ڵ������
};

/**********************************************************/
/**
 * @brief ���� xini_node_t �������������������
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
 * @brief INI �ļ��еĿ��нڵ��ࡣ
 */
class xini_nilline_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief ����ʹ���ַ���ֱ�Ӵ�������ʼ�� xini_nilline_t ����
     *
     * @param [in ] xstr_line  :
     *  ���ڴ��� ���нڵ� ���ַ����У�
     *  ���Ѿ��� trim_xstr() �޼�ǰ��˵Ŀհ��ַ���
     *
     * @param [in ] xowner_ptr :
     *  ��ֵ�ڵ��ӵ���ߣ�xini_section_t ���ͣ���
     *
     * @return xini_node_t * :
     *  �����ɹ������ص� ���нڵ㣻��ʧ�ܣ��򷵻� NULL ��
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
     * @brief �� �ڵ���Ϣ ���� �������
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
 * @brief INI �ļ��е� ע�� �ڵ��ࡣ
 */
class xini_comment_t : public xini_node_t
{
    friend class xini_file_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief ����ʹ���ַ���ֱ�Ӵ�������ʼ�� xini_comment_t ����
     *
     * @param [in ] xstr_line  :
     *  ���ڴ��� ע�ͽڵ� ���ַ����У�
     *  ���Ѿ��� trim_xstr() �޼�ǰ��˵Ŀհ��ַ���
     *
     * @param [in ] xowner_ptr :
     *  ��ֵ�ڵ��ӵ���ߣ�xini_section_t ���ͣ���
     *
     * @return xini_node_t * :
     *  �����ɹ������ص� ע�ͽڵ㣻��ʧ�ܣ��򷵻� NULL ��
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
     * @brief �� �ڵ���Ϣ ���� �������
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
     * @brief ע�����ַ��� ���ݡ�
     */
    inline const std::string& text(void) const { return m_xstr_text; }

protected:
    std::string   m_xstr_text;  ///< ע�����ַ���
};

////////////////////////////////////////////////////////////////////////////////
// xini_keyvalue_t

/**
 * @class xini_keyvalue_t
 * @brief INI �ļ��е� �ֽ� �ڵ��ࡣ
 */
class xini_keyvalue_t : public xini_node_t
{
    friend class xini_file_t;
    friend class xini_section_t;

    // common invoking
protected:
    /**********************************************************/
    /**
     * @brief �������ַ�����ʽ�Ƿ���Ч��
     *
     * @param [in ] xstr_name :
     *  ������ ���������Ѿ��� trim_xstr() �޼���ǰ��˵Ŀհ��ַ���
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
     * @brief ����ʹ���ַ���ֱ�Ӵ�������ʼ�� xini_keyvalue_t ����
     *
     * @param [in ] xstr_line  :
     *  ���ڴ��� ��ֵ�ڵ� ���ַ����У����Ѿ��� trim_xstr() �޼�ǰ��˵Ŀհ��ַ���
     *
     * @param [in ] xowner_ptr : ��ֵ�ڵ��ӵ���ߣ�xini_section_t ���ͣ���
     *
     * @return xini_node_t * :
     *  �����ɹ������ص� ��ֵ�ڵ㣻��ʧ�ܣ��򷵻� NULL ��
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

        // �Ⱥ�λ��
        size_t st_eq = xstr_line.find('=');
        if ((0 == st_eq) || (std::string::npos == st_eq))
        {
            return NULL;
        }

        // ����
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
     * @brief �� �ڵ���Ϣ ���� �������
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
     * @brief ��ֵ�Ķ�������
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
     * @brief ��ֵ�Ķ���������Ĭ��ֵ����
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
     * @brief ��ֵ��д������
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
     * @brief ��ֵ��д������
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
     * @brief ��ֵ�Ķ���������ֵΪ �գ����ʽ�Ƿ���ʱ��ͬ��д��Ĭ��ֵ����
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
     * @brief ��ֵ�Ķ���������ֵΪ �գ����ʽ�Ƿ���ʱ��ͬ��д��Ĭ��ֵ����
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
     * @brief bool ֵ�Ķ���������ֵΪ �գ����ʽ�Ƿ���ʱ��ͬ��д��Ĭ��ֵ����
     */
    bool try_bool(bool x_default)
    {
        //======================================
        // �� �ַ��� ����

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
        // �� ����ֵ ����

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
    // �����������͵Ķ�����

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
    // ���� operator ()��ʵ�ִ���Ĭ��ֵ�Ķ�����

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
    // �����ص� operator () ��Ĭ��ֵ��ȡ�������������ƣ�
    // ����ֵΪ �գ����ʽ�Ƿ���ʱ����ͬ��д��Ĭ��ֵ

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
    // �����������͵�д����

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
     * @brief ��ֵ�ڵ��໥��ֵʱ��ֻ ȡֵ �� ���� ������
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
     * @brief ������
     */
    inline const std::string& key(void) const
    {
        return m_xstr_kname;
    }

    /**********************************************************/
    /**
     * @brief ��ֵ��
     */
    inline const std::string& value(void) const
    {
        return m_xstr_value;
    }

    /**********************************************************/
    /**
     * @brief �ж� ��ֵ �Ƿ�Ϊ �ա�
     */
    inline bool empty(void) const
    {
        return m_xstr_value.empty();
    }

    /**********************************************************/
    /**
     * @brief �޸ļ�����
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
     * @brief ���ü�ֵ��
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
     * @brief ���ã������ı� �� ȥ��ͷβ�հ��ַ� �ģ���ֵ��
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
    std::string   m_xstr_kname;  ///< ����
    std::string   m_xstr_value;  ///< ��ֵ
};

////////////////////////////////////////////////////////////////////////////////
// xini_section_t

/**
 * @class xini_section_t
 * @brief INI �ļ��е� �ֽ� �ڵ��ࡣ
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
     * @brief �޼� �ֽ����ַ��� ǰ��˶�����ַ���
     */
    static inline std::string trim_sname(const std::string& xstr_name)
    {
        return trim_xstr(xstr_name, "[] \t\n\r\f\v");
    }

    /**********************************************************/
    /**
     * @brief ���ֽ����ַ�����ʽ�Ƿ���Ч��
     *
     * @param [in ] xstr_name :
     *  ������ �ֽ���������ǰ���Ѿ���
     *  trim_sname() �޼���ǰ��˶�����ַ���
     */
    static inline bool check_sname(const std::string& xstr_name)
    {
        assert(is_xtrim(xstr_name));
        return is_sline(xstr_name);
    }

    /**********************************************************/
    /**
     * @brief ����ʹ���ַ���ֱ�Ӵ�������ʼ�� xini_section_t ����
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

        // �� ���� ��Ϊ �ڵ� ���뵽 m_xlst_node �У���������ζ�� m_xlst_node 
        // �� �׸��ڵ� ��һ���� ����ڵ㣬��Ϊ xini_file_t �ڼ��ع����У�
        // ����� pop_tail_comment() ���������п����� m_xlst_node ǰ������
        // һЩ ע��/���нڵ㡣�����ڽ��� ����� ����ʱ������ڵ� ����� ռλ��
        // �����ã���ϸ���̿ɲο� operator >> ��ʵ������
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
     * @brief �� �ڵ���Ϣ ���� �������
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
     * @brief �������������ӽڵ㣨��ֵ�ڵ㣩����������
     * @note  �ýӿڽ��� xini_keyvalue_t::set_key() ���á�
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
     * @brief ���� operator [] ��������ʵ�� ��ֵ �ڵ������������
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
        // �������� ��ֵ�ڵ� ��δ�ڽڵ���У�
        // �� ���� �� ��ֵ�ڵ㣬���������� ���ʶ��
        // ����洢����Ҫ�� �ռ�ֵ�ڵ�

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
     * @brief �ֽ� ���ơ�
     */
    inline const std::string& name(void) const
    {
        return m_xstr_name;
    }

    /**********************************************************/
    /**
     * @brief �޸� �ֽ� ���ơ�
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
     * @brief �ֽ� �ڵĽڵ�������
     */
    inline size_t size(void) const
    {
        return m_xlst_node.size();
    }

    /**********************************************************/
    /**
     * @brief �ֽ� �Ƿ�Ϊ�ա�
     */
    inline bool empty() const
    {
        return m_xlst_node.empty();
    }

    /**********************************************************/
    /**
     * @brief �жϵ�ǰ�ֽ��Ƿ��Կ��н�β��
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
     * @brief �ж���ǰ�Ƿ��Ѿ�����ָ���� ��ֵ�ڵ㡣
     */
    inline bool key_included(const std::string& xstr_key) const
    {
        return (NULL != find_knode(trim_xstr(xstr_key)));
    }

    /**********************************************************/
    /**
     * @brief �� ��ֵ�ڵ� ����������������������������
     *
     * @param [in ] xstr_key  : Ŀ�����������������
     * @param [in ] xstr_name : �������ü�ֵ�ڵ������������
     *
     * @return ���������� �Ƿ�ɹ���
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
     * @brief ɾ��ָ����ֵ��
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
     * @brief �ڵ�����ʼλ�õ�������
     */
    inline iterator begin(void) { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief �ڵ�����ʼλ�õ�������
     */
    inline const_iterator begin(void) const { return m_xlst_node.begin(); }

    /**********************************************************/
    /**
     * @brief �ڵ��Ľ���λ�õ�������
     */
    inline iterator end(void) { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief �ڵ��Ľ���λ�õ�������
     */
    inline const_iterator end(void) const { return m_xlst_node.end(); }

    /**********************************************************/
    /**
     * @brief ���ؽڵ���� �׸� ��ֵ�ڵ� �ĵ�������
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
     * @brief ���ؽڵ���� �׸� ��ֵ�ڵ� �ĵ�������
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
     * @brief ���� ��һ�� ��ֵ�ڵ� �ĵ�������
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
     * @brief ���� ��һ�� ��ֵ�ڵ� �ĵ�������
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
     * @brief ��ӣ����С�ע�͡���ֵ ���͵ģ��ڵ㡣
     *
     * @param [in ] xnode_ptr: �����С�ע�͡���ֵ ���͵ģ��ڵ㡣
     *
     * @return �����Ƿ�ɹ���
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
     * @brief ���ҷֽ��µ� ��ֵ �ڵ㡣
     *
     * @param [in ] xstr_xkey: �������ַ������Ƚ�ʱ���Դ�Сд��
     *
     * @return xini_keyvalue_t *
     *         - �ɹ������� ��Ӧ�Ľڵ㣻
     *         - ʧ�ܣ����� NULL ��
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
     * @brief �� �ڵ�� β��ȡ�� �ǵ�ǰ �ֽ� �µ�ע�ͽڵ㣨�� ���� �ڵ���Ϊ�ֽ磩��
     *
     * @param [in ] xlst_comm : ���շ��ص�ע�ͽڵ��������ͷ����ӷ��صĽڵ㣩��
     * @param [in ] xbt_front : ���������Ǵ� xlst_comm ǰ/�󸽼ӷ��صĽڵ㡣
     *
     * @return size_t
     *         - ����ȡ���Ľڵ�������
     */
    size_t pop_tail_comment(std::list< xini_node_t* >& xlst_comm, bool xbt_front)
    {
        std::list< xini_node_t* > xlst_node;

        size_t xst_line = 0;
        size_t xst_maxl = m_xlst_node.size();

        // �ڵ��ֻ���������͵Ľڵ㣺��ֵ�����У�ע�ͣ�
        // �Լ� ������� ����� �ֽڽڵ�

        while ((xst_line++ < xst_maxl) && !m_xlst_node.empty())
        {
            xini_node_t* xnode_ptr = m_xlst_node.back();

            // �������нڵ�
            if (XINI_NTYPE_NILLINE == xnode_ptr->ntype())
            {
                if (xst_line > 1)
                    break;

                // ֻ�����һ���ǿ���
                xlst_node.push_front(xnode_ptr);
                m_xlst_node.pop_back();
                continue;
            }

            // ��������������У�һֱδ�������У�
            // ��ԭȡ����ע�ͽڵ㻹�ؽڵ����
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
                // δʶ��Ľڵ�����
                assert(false);
            }
        }

        size_t xst_count = xlst_node.size();
        if (xst_count > 0)
        {
            // ���÷��ؽ��
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
     * @brief �� ��ֵ�ڵ� ����������������
     *
     * @param [in ] xndkv_ptr : Ŀ������ļ�ֵ�ڵ㡣
     * @param [in ] xstr_name : �������ü�ֵ�ڵ������������
     *
     * @return ���������� �Ƿ�ɹ���
     */
    bool rename_knode(xini_keyvalue_t* xndkv_ptr, const std::string& xstr_name)
    {
        //======================================

        // ���ֵ�ڵ�ԭ������һ�£����Ժ�������
        if (0 == xstr_icmp(xndkv_ptr->key().c_str(), xstr_name.c_str()))
        {
            return true;
        }

        // �ж���Ҫ���õļ�ֵ�ڵ����ƣ�
        // ��ڵ���е�������ֵ�ڵ����� �Ƿ�����
        if (NULL != find_knode(xstr_name))
        {
            return false;
        }

        //======================================
        // �ȴ�ӳ������Ƴ����еļ�ֵ�ڵ�ӳ�䣬
        // �ٶԼ�ֵ�ڵ������������������¼��뵽ӳ�����

        m_xmap_ndkv.erase(xndkv_ptr->key());
        xndkv_ptr->m_xstr_kname = xstr_name;
        m_xmap_ndkv.insert(std::make_pair(xndkv_ptr->key(), xndkv_ptr));

        set_dirty(true);

        //======================================

        return true;
    }

protected:
    std::string   m_xstr_name;  ///< �ֽ�����
    xlst_node_t   m_xlst_node;  ///< �ֽ��µĽڵ��
    xmap_ndkv_t   m_xmap_ndkv;  ///< �ֽ��µ� ��ֵ�ڵ� ӳ���
};

////////////////////////////////////////////////////////////////////////////////
// xini_file_t

/**
 * @class xini_file_t
 * @brief INI �ļ������ࡣ
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
     * @brief ���ݸ����� INI �ı��У�������Ӧ�Ľڵ㡣
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
     * @brief �� �ڵ���Ϣ ���� �������
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
     * @brief ���ʶ��
     */
    virtual bool is_dirty(void) const
    {
        return m_xbt_dirty;
    }

    /**********************************************************/
    /**
     * @brief �������ʶ��
     */
    virtual void set_dirty(bool x_dirty)
    {
        m_xbt_dirty = x_dirty;
    }

protected:
    /**********************************************************/
    /**
     * @brief �������������ӽڵ㣨�ֽڽڵ㣩����������
     * @note  �ýӿڽ��� xini_section_t::set_name() ���á�
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
     * @brief �� ����� ���� xini_file_t ���ݡ�
     */
    xini_file_t& operator << (std::istream& istr)
    {
        //======================================

        // ��¼��ǰ�����ķֽ�
        xini_section_t* xsect_ptr = NULL;

        if (m_xlst_sect.empty())
        {
            // ��ǰ�ֽڱ�Ϊ�գ��򴴽�һ���շֽ����� �ֽ� �ڵ�
            xsect_ptr = new xini_section_t(this);
            m_xlst_sect.push_back(xsect_ptr);

            assert(m_xmap_sect.empty());
            m_xmap_sect.insert(std::make_pair(std::string(""), xsect_ptr));
        }
        else
        {
            // ȡβ���ֽ���Ϊ��ǰ������ �ֽ� �ڵ�
            xsect_ptr = m_xlst_sect.back();

            // ȷ��β���ֽڿ��н�β
            if (!xsect_ptr->has_end_nilline())
            {
                xsect_ptr->push_node(new xini_nilline_t(this));
            }
        }

        //======================================

        // ���н��� INI �ļ��������ڵ��
        while (!istr.eof())
        {
            //======================================
            // ��ȡ�ı���

            std::string xstr_line;
            std::getline(istr, xstr_line);
            xstr_line = trim_xstr(xstr_line);

            // ���һ�����в��ŵ��ڵ���У������ļ��ر�ʱ �������� β������
            if (istr.eof() && xstr_line.empty())
            {
                break;
            }

            //======================================

            // �����ڵ�
            xini_node_t* xnode_ptr = make_node(xstr_line, this);
            if (NULL == xnode_ptr)
            {
                continue;
            }

            // ��Ϊ �ֽ� �ڵ㣬����뵽�ֽڱ��У������µ�ǰ������ �ֽڽڵ�
            if (XINI_NTYPE_SECTION == xnode_ptr->ntype())
            {
                xsect_ptr =
                    push_sect(static_cast<xini_section_t*>(xnode_ptr),
                        xsect_ptr);

                if (xsect_ptr != static_cast<xini_section_t*>(xnode_ptr))
                    delete xnode_ptr; // ����·ֽ�ʧ�ܣ�ɾ���ýڵ�
                else
                    set_dirty(true);  // ����·ֽڳɹ����������ʶ

                continue;
            }

            // ���� ��ǰ�ֽ�
            if (xsect_ptr->push_node(xnode_ptr))
            {
                set_dirty(true);
            }
            else
            {
                // ����ֽ�ʧ�ܣ���������Ϊ��
                // ��Ϊ ��ֵ �ڵ㣬�� �ֽ� �ڵ�������е� �ڵ� ������ ��ͻ
                delete xnode_ptr;
            }

            //======================================
        }

        //======================================

        return *this;
    }

    /**********************************************************/
    /**
     * @brief ���� operator [] ��������ʵ�� �ֽ� ����������
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
        // �������ķֽڲ�δ�� �ֽ� �Ľڵ���У�
        // �� ���� �˷ֽڣ����������� ���ʶ��
        // ����洢����Ҫ��  �շֽ�

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
     * @brief ��ָ��·�����ļ��м��� INI ���ݡ�
     * @note
     *  load() �����ĳɹ���񣬲���Ӱ������ļ�ֵ��д������
     *  ��ֻ�ܱ�ʾ xini_file_t �����Ƿ��������ָ��·��
     *  �����ش��� �� Զ������ �ȵģ��ļ���
     *
     * @param [in ] xstr_text : �ļ�·����
     *
     * @return bool
     *         - �ɹ������� true ��
     *         - ʧ�ܣ����� false��
     */
    bool load(const std::string& xstr_filepath)
    {
        // ���ͷŵ�ǰ����
        release();

        // ���ܺ��������Ƿ�ɹ�������������ָ���� INI �ļ�·��
        m_xstr_path = xstr_filepath;

        if (xstr_filepath.empty())
        {
            return false;
        }

        // ���ļ�
        std::ifstream xfile_reader(xstr_filepath.c_str());
        if (!xfile_reader.is_open())
        {
            return false;
        }

        // �����ַ�����ͷ��������Ϣ���� utf-8 �� bom ��ʶ��
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
     * @brief ����ǰ�ļ����µ����нڵ�ֱ��������ļ��С�
     */
    bool dump(const std::string& xstr_filepath)
    {
        // ���ļ�
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
     * @brief �ͷŶ�����Դ�����Բ���ʾ���ã��������������л��Զ����øýӿڣ���
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
     * @brief ��ǰ�������ļ�·����
     */
    inline const std::string& filepath(void) const
    {
        return m_xstr_path;
    }

    /**********************************************************/
    /**
     * @brief ���ص�ǰ�ֽ�������
     */
    inline size_t sect_count(void) const
    {
        return m_xlst_sect.size();
    }

    /**********************************************************/
    /**
     * @brief �ж���ǰ�Ƿ����ָ���� �ֽڡ�
     */
    inline bool sect_included(const std::string& xstr_sect) const
    {
        return (NULL != find_sect(xini_section_t::trim_sname(xstr_sect)));
    }

    /**********************************************************/
    /**
     * @brief �� �ֽ� ����������������
     *
     * @param [in ] xstr_sect : Ŀ������ķֽ����ơ�
     * @param [in ] xstr_name : �������÷ֽڵ����ơ�
     *
     * @return ���������� �Ƿ�ɹ���
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
     * @brief ɾ��ָ���ֽڡ�
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
     * @brief �ֽڱ����ʼλ�õ�������
     */
    inline iterator begin(void) { return m_xlst_sect.begin(); }

    /**********************************************************/
    /**
     * @brief �ֽڱ����ʼλ�õ�������
     */
    inline const_iterator begin(void) const { return m_xlst_sect.begin(); }

    /**********************************************************/
    /**
     * @brief �ֽڱ�Ľ���λ�õ�������
     */
    inline iterator end(void) { return m_xlst_sect.end(); }

    /**********************************************************/
    /**
     * @brief �ֽڱ�Ľ���λ�õ�������
     */
    inline const_iterator end(void) const { return m_xlst_sect.end(); }

    // inner invoking
protected:
    /**********************************************************/
    /**
     * @brief ���ҷֽڡ�
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
     * @brief �����·ֽڣ��ýӿڽ��� operator << ���ã���
     *
     * @param [in ] xnew_ptr  : �����ֽڡ�
     * @param [in ] xsect_ptr : ��ǰ�����ֽڡ�
     *
     * @return xini_section_t *
     *         - ���ص�ǰ�����ֽڡ�
     *         - ������ֵ != xnew_ptr ���ʾ����ʧ�ܣ������ֽں��ڲ��ֽ�������
     */
    xini_section_t* push_sect(xini_section_t* xnew_ptr,
        xini_section_t* xsect_ptr)
    {
        // ����ͬ���ֽ�
        xini_section_t* xfind_ptr = find_sect(xnew_ptr->name());

        if (NULL == xfind_ptr)
        {
            // ������ͬ���ֽڣ��������ֽڼ��뵽�ڵ��β��
            m_xlst_sect.push_back(xnew_ptr);
            m_xmap_sect.insert(std::make_pair(xnew_ptr->name(), xnew_ptr));

            // ����ǰ�����ֽڵĽڵ���е� β��ע�ͽڵ㣬
            // ȫ��ת�Ƶ������ֽڵĽڵ��ǰ
            xsect_ptr->pop_tail_comment(xnew_ptr->m_xlst_node, true);

            // �������ֽ���Ϊ��ǰ�����ֽڷ���
            xsect_ptr = xnew_ptr;
        }
        else if (xfind_ptr != xsect_ptr)
        {
            // ����ǰ�����ֽڵĽڵ���е� β��ע�ͽڵ㣬
            // ȫ��ת�Ƶ�ͬ���ֽڵĽڵ���

            // ��֤���и���
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));
            }

            // ����ע�ͽڵ�
            xsect_ptr->pop_tail_comment(xfind_ptr->m_xlst_node, false);

            // ��֤���и���
            if (!xfind_ptr->has_end_nilline())
            {
                xfind_ptr->push_node(new xini_nilline_t(this));
            }

            // ��ͬ���ֽ���Ϊ��ǰ�����ֽڷ���
            xsect_ptr = xfind_ptr;
        }

        return xsect_ptr;
    }

    /**********************************************************/
    /**
     * @brief �� �ֽ� ����������������
     *
     * @param [in ] xsect_ptr : Ŀ������ķֽڡ�
     * @param [in ] xstr_name : �������÷ֽڵ����ơ�
     *
     * @return ���������� �Ƿ�ɹ���
     */
    bool rename_sect(xini_section_t* xsect_ptr, const std::string& xstr_name)
    {
        //======================================

        // ��ֽ�ԭ������һ�£����Ժ�������
        if (0 == xstr_icmp(xsect_ptr->name().c_str(), xstr_name.c_str()))
        {
            return true;
        }

        // �ж���Ҫ���õķֽ����ƣ�
        // ��ֽڱ��е������ֽ����� �Ƿ�����
        if (NULL != find_sect(xstr_name))
        {
            return false;
        }

        //======================================
        // �ȴ�ӳ������Ƴ����еķֽڽڵ�ӳ�䣬
        // �ٶԷֽڽ�����������������¼��뵽ӳ�����

        m_xmap_sect.erase(xsect_ptr->name());
        xsect_ptr->m_xstr_name = xstr_name;
        m_xmap_sect.insert(std::make_pair(xsect_ptr->name(), xsect_ptr));

        set_dirty(true);

        //======================================

        return true;
    }

    // data members
protected:
    bool              m_xbt_dirty;  ///< ���ʶ
    std::string       m_xstr_path;  ///< �ļ�·��
    std::string       m_xstr_head;  ///< ���ڴ洢�ļ�ͷ�ı����ַ���Ϣ���� utf-8 �� bom ��ʶ��
    xlst_section_t    m_xlst_sect;  ///< �ļ����µ� �ֽ� �ڵ��
    xmap_section_t    m_xmap_sect;  ///< ���� �ֽ� �Ľڵ�ӳ���
};

/**********************************************************/
/**
 * @brief ���� xini_file_t �������������������
 */
inline std::istream& operator >> (
    std::istream& istr, xini_file_t& xini_file)
{
    xini_file << istr;
    return istr;
}

////////////////////////////////////////////////////////////////////////////////

#endif // __XINI_FILE_H__
