<!--
   - Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
   - Software License, Version 1.0. (See accompanying file
   - LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
   -
   - XSLT template used for generating header files implementing
   - specializations of the Bound<Object> template.
  -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="text"/>
	<xsl:strip-space elements="*"/>
	<xsl:preserve-space elements="xsl:text"/>

	<xsl:template name="Newline"><xsl:text>&#x0A;</xsl:text></xsl:template>

	<xsl:param name="object"/>
	<xsl:param name="year"/>

	<xsl:template name="Capitalize">
		<xsl:param name="String"/>
		<xsl:value-of select="translate(
			$String,
			'abcdefghijklmnopqrstuvwxyz',
			'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
		)"/>
	</xsl:template>

	<xsl:template name="CapitalizeFirst">
		<xsl:param name="String"/>
		<xsl:call-template name="Capitalize">
			<xsl:with-param name="String" select="substring($String, 1, 1)"/>
		</xsl:call-template>
		<xsl:value-of select="substring($String, 2)"/>
	</xsl:template>

	<xsl:variable name="Object">
		<xsl:call-template name="CapitalizeFirst">
			<xsl:with-param name="String" select="$object"/>
		</xsl:call-template>
	</xsl:variable>

	<xsl:variable name="OBJECT">
		<xsl:call-template name="Capitalize">
			<xsl:with-param name="String" select="$object"/>
		</xsl:call-template>
	</xsl:variable>

	<xsl:template match="*">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template name="GenerateFunction">
		<xsl:variable name="DetailedDescription">
			<xsl:for-each select="detaileddescription/descendant-or-self::node()">
				<xsl:value-of select="text()"/><xsl:text> </xsl:text>
			</xsl:for-each>
		</xsl:variable>
		<xsl:variable name="RequiredGLVersion">
			<xsl:if test="contains(
				$DetailedDescription,
				'_oglplus_req_gl_ver('
			)">
				<xsl:value-of select="substring-before(
					substring-after(
						$DetailedDescription,
						'_oglplus_req_gl_ver('
					), ')'
				)"/>
			</xsl:if>
		</xsl:variable>
		<xsl:variable name="RequiredGLExtension">
			<xsl:if test="contains(
				$DetailedDescription,
				'_oglplus_req_gl_ext('
			)">
				<xsl:value-of select="substring-before(
					substring-after(
						$DetailedDescription,
						'_oglplus_req_gl_ext('
					), ')'
				)"/>
			</xsl:if>
		</xsl:variable>
		<xsl:if test="string-length($RequiredGLVersion) != 0">
			<xsl:text>#if OGLPLUS_DOCUMENTATION_ONLY || GL_VERSION_</xsl:text>
			<xsl:value-of select="$RequiredGLVersion"/>
			<xsl:if test="string-length($RequiredGLExtension) != 0">
				<xsl:text> || GL_</xsl:text>
				<xsl:value-of select="$RequiredGLExtension"/>
			</xsl:if>
			<xsl:call-template name="Newline"/>
		</xsl:if>
		<xsl:text>
	/** Wrapper for </xsl:text>
		<xsl:value-of select="$Object"/>
		<xsl:text>::</xsl:text>
		<xsl:value-of select="name/text()"/>
		<xsl:text>()
	 *  @see </xsl:text>
		<xsl:value-of select="$Object"/>
		<xsl:text>::</xsl:text>
		<xsl:value-of select="name/text()"/>
		<xsl:text>()
	 */</xsl:text><xsl:call-template name="Newline"/>
		<xsl:for-each select="templateparamlist">
			<xsl:text>	template &lt;</xsl:text>
			<xsl:for-each select="param">
				<xsl:value-of select="type/text()"/>
				<xsl:if test="declname">
					<xsl:text> </xsl:text>
					<xsl:value-of select="declname/text()"/>
				</xsl:if>
				<xsl:if test="position() != last()">, </xsl:if>
			</xsl:for-each>
			<xsl:text>&gt;</xsl:text>
			<xsl:call-template name="Newline"/>
		</xsl:for-each>
		<xsl:text>	</xsl:text>
		<xsl:variable name="RVRefId" select="type/ref/@refid"/>
		<xsl:if test="../../sectiondef/memberdef[@id = $RVRefId]">
			<xsl:value-of select="$Object"/>
			<xsl:text>Ops::</xsl:text>
		</xsl:if>
		<xsl:for-each select="type/descendant-or-self::text()">
			<xsl:value-of select="."/>
		</xsl:for-each>
		<xsl:text> </xsl:text>
		<xsl:value-of select="name/text()"/>
		<xsl:text>(</xsl:text>

		<xsl:variable
			name="HasParams"
			select="count(param[type/descendant-or-self::text() != 'Target']) != 0"
		/>

		<xsl:choose>
			<xsl:when test="$HasParams">
				<xsl:call-template name="Newline"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:text>void</xsl:text>
			</xsl:otherwise>
		</xsl:choose>
		
		<xsl:for-each select="param">
			<xsl:variable name="Type">
				<xsl:for-each select="type/descendant-or-self::text()">
					<xsl:value-of select="."/>
				</xsl:for-each>
			</xsl:variable>
			<xsl:variable name="TypePrefix">
				<xsl:variable name="RefId" select="type/ref/@refid"/>
				<xsl:if test="../../../sectiondef/memberdef[@id = $RefId]">
					<xsl:value-of select="$Object"/>
					<xsl:text>Ops::</xsl:text>
				</xsl:if>
				<xsl:if test="../../../../compounddef[
					contains(compoundname, concat($Object,'Ops::'))
				]/sectiondef/memberdef[@id = $RefId]">
					<xsl:value-of select="$Object"/>
					<xsl:text>Ops::</xsl:text>
				</xsl:if>
			</xsl:variable>
			<xsl:if test="$Type != 'Target'">
				<xsl:text>		</xsl:text>
				<xsl:value-of select="$TypePrefix"/>
				<xsl:value-of select="$Type"/>
				<xsl:text> </xsl:text>
				<xsl:choose>
					<xsl:when test="declname/text()">
						<xsl:value-of select="declname/text()"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>_auto_param_</xsl:text>
						<xsl:value-of select="position()"/>
					</xsl:otherwise>
				</xsl:choose>
				<xsl:if test="defval">
					<xsl:text> = </xsl:text>
					<xsl:value-of select="$TypePrefix"/>
					<xsl:value-of select="defval/text()"/>
				</xsl:if>
				<xsl:if test="position() != last()">,</xsl:if>
				<xsl:call-template name="Newline"/>
			</xsl:if>
		</xsl:for-each>

		<xsl:if test="$HasParams">
			<xsl:text>	</xsl:text>
		</xsl:if>
		<xsl:text>) const</xsl:text>
		<xsl:call-template name="Newline"/>
		<xsl:text>	{</xsl:text>
		<xsl:call-template name="Newline"/>
		<xsl:text>		</xsl:text>
		<xsl:if test="type/text() != 'void'">
			<xsl:text>return </xsl:text>
		</xsl:if>
		<xsl:value-of select="$Object"/>
		<xsl:text>Ops::</xsl:text>
		<xsl:value-of select="name/text()"/>
		<xsl:text>(</xsl:text>
		<xsl:call-template name="Newline"/>
		<xsl:for-each select="param">
			<xsl:text>			</xsl:text>
			<xsl:variable name="Type">
				<xsl:value-of select="type/ref/text()"/>
				<xsl:value-of select="type/text()"/>
			</xsl:variable>
			<xsl:if test="$Type != 'Target'">
				<xsl:choose>
					<xsl:when test="declname/text()">
						<xsl:value-of select="declname/text()"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>_auto_param_</xsl:text>
						<xsl:value-of select="position()"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:if>
			<xsl:if test="$Type='Target'">
				<xsl:text>this-&gt;BindTarget()</xsl:text>
			</xsl:if>
			<xsl:if test="position() != last()">,</xsl:if>
			<xsl:call-template name="Newline"/>
		</xsl:for-each>
		<xsl:text>		);</xsl:text>
		<xsl:call-template name="Newline"/>
		<xsl:text>	}</xsl:text>
		<xsl:call-template name="Newline"/>

		<xsl:if test="string-length($RequiredGLVersion) != 0">
			<xsl:text>#endif // GL_VERSION_</xsl:text>
			<xsl:value-of select="$RequiredGLVersion"/>
			<xsl:if test="string-length($RequiredGLExtension) != 0">
				<xsl:text> || GL_</xsl:text>
				<xsl:value-of select="$RequiredGLExtension"/>
			</xsl:if>
			<xsl:call-template name="Newline"/>
		</xsl:if>
	</xsl:template>

	<xsl:template name="GenerateHeader">
<xsl:text>
/**
 *  @file oglplus/bound/</xsl:text><xsl:value-of select="$object"/><xsl:text>.hpp
 *  @brief Specialization of BoundTemplate for </xsl:text><xsl:value-of select="$Object"/><xsl:text>.
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-</xsl:text>
	<xsl:value-of select="$year"/>
<xsl:text> Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef OGLPLUS_BOUND_</xsl:text><xsl:value-of select="$OBJECT"/><xsl:text>_1107121519_HPP
#define OGLPLUS_BOUND_</xsl:text><xsl:value-of select="$OBJECT"/><xsl:text>_1107121519_HPP

#include &lt;oglplus/</xsl:text><xsl:value-of select="$object"/><xsl:text>.hpp&gt;
#include &lt;oglplus/bound.hpp&gt;
#include &lt;oglplus/auto_bind.hpp&gt;
#include &lt;utility&gt;

namespace oglplus {

/// Specialization of the BoundTemplate for </xsl:text>
	<xsl:value-of select="$Object"/>
<xsl:text>Ops, implements Bound &lt; </xsl:text> 
	<xsl:value-of select="$Object"/>
<xsl:text>  &gt;.
/** This template implements wrappers around the member functions
 *  of </xsl:text><xsl:value-of select="$Object"/><xsl:text>, which have
 *  a </xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops::Target parameter
 *  specifying the binding point on which they should operate.
 *
 *  @note Do not use this template class directly use
 *  Bound &lt; </xsl:text><xsl:value-of select="$Object"/><xsl:text> &gt; or the Bind()
 *  function instead.
 *
 *  @see Bind()
 *  @see Bound
 *  @see AutoBind
 *
 *  @ingroup utility_classes
 */
template &lt;template &lt;class&gt; class Base, class BaseParam&gt;
class BoundTemplate&lt;Base, BaseParam, </xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops&gt;
 : public Base&lt;BaseParam&gt;
{
public:
	BoundTemplate(
		const </xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops&amp; bindable,
		</xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops::Target target
	): Base&lt;</xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops&gt;(bindable, target)
	{ }

	BoundTemplate(
		</xsl:text><xsl:value-of select="$Object"/><xsl:text>Ops::Target target
	): Base&lt;BaseParam&gt;(target)
	{ }

</xsl:text>
	<xsl:for-each select="sectiondef/memberdef[
		@kind='function' and
		@prot='public' and
		param/declname/text()='target' and
		(param/type/text()='Target' or param/type/ref/text()='Target') and
		name/text() != 'Bind' and
		name/text() != 'Unbind'
	]">
		<xsl:call-template name="GenerateFunction"/>
		<xsl:call-template name="Newline"/>
	</xsl:for-each>

<xsl:text>
}; // class BoundTemplate

} // namespace oglplus

#endif // include guard
</xsl:text>
	</xsl:template>

	<xsl:template match="/doxygen/compounddef">
		<xsl:if test="compoundname/text()=(concat('oglplus::', $Object,'Ops'))">
			<xsl:call-template name="GenerateHeader"/>
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>
