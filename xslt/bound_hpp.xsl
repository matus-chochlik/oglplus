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
	</xsl:template>

	<xsl:template name="GenerateHeader">
<xsl:text>
/**
 *  @file oglplus/bound/</xsl:text><xsl:value-of select="$object"/><xsl:text>.hpp
 *  @brief BoundTemplate </xsl:text><xsl:value-of select="$Object"/><xsl:text> wrapper
 *
 *  Automatically generated file, do not edit manually!
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
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
