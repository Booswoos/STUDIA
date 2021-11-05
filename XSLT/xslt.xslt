<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:msxsl="urn:schemas-microsoft-com:xslt" exclude-result-prefixes="msxsl"
>


  <xsl:template match="/">
    <html>
      <head></head>
      <body style="margin-left:300px; margin-right:300px;background-color:#fffff0">
        <xsl:apply-templates/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="spis"> 
    <h2 style ="color:red;text-align:center">
      <xsl:value-of select="komentarz"/>
    </h2>

    
      
      
      <h2>Towary</h2>
 <table border="2px solid black">
      <xsl:apply-templates select="towar"/>
    </table>

     
   
    <br>
    </br>
    <div style="font-family:Arial;font-size:12pt;background-color:#EEEEEE"> Informacje </div>
    
  
       <xsl:apply-templates select="towar/inf" />


    <div style="font-family:Arial;font-size:12pt;background-color:#EEEEEE"> Uslugi </div>
    <div class="usluga" style="background-color:khaki"  >
      <xsl:apply-templates select="usluga" />
     
    </div>
    
    <div style="font-family:Arial;font-size:12pt;background-color:#EEEEEE"> Numery </div>
    <div style="background-color:gray">
    <xsl:apply-templates select="usluga/wykonawca/numer"/>  
    </div>
  </xsl:template>
  
  
  <xsl:template match="towar">
    
    
        <tr bgcolor="#04cd32">
          <th style="text-align:left">Numer</th>
          <th style="text-align:left">Produkt</th>
          <th style="text-align:left">Ilosc</th>
          <th style="text-align:left">Kwota</th>
          <th style="text-align:left">Waluta</th>
        </tr>
        <xsl:for-each select=".">
          <xsl:sort select="inf/nazwa"/>
          <tr>
            <td>
              <xsl:number format="I" value="position()"/>
            </td>
            <td>
              <xsl:value-of select="translate(inf/nazwa,'abcdefghijklmnopqrstuvwxyzłąćńóźż', 'ABCDEFGHIJKLMNOPQRSTUVWXYZŁĄĆŃÓŹŻ')"/>
            </td>
            <td>
              <xsl:value-of select="ilosc[1]"/>
            </td>
            
            <xsl:choose>
              <xsl:when test="suma > 200">
                <td bgcolor="#ff00ff">
                  <xsl:value-of select="suma[last()]"/>
                </td>
              </xsl:when>
              <xsl:otherwise>
                <td>
                  <xsl:value-of select="suma[last()]"/>
                </td>
              </xsl:otherwise>
            </xsl:choose>
            
            <td>
              <xsl:value-of select="suma/@waluta" />
            </td>
          </tr>
        </xsl:for-each>
      
    
  
  </xsl:template>


  <xsl:template match="towar/inf">
    <div class="inf" style="background-color:#FFFF10;float:left;">
    <span style="font-weight:bold;text-align:left;">

      <xsl:variable name="index">
        <xsl:number format="1" value="position()"/>
      </xsl:variable>

      <span style="color:purple; font-size:22px">
      <xsl:value-of select="concat($index,'. ')"/>
      <xsl:value-of select="./nazwa"/>
      </span>
      <br></br>
      <xsl:apply-templates select="./image"/>
      <xsl:apply-templates select="./opis"/>
      <br></br>
      <a href="{@link}">
        <xsl:value-of select="@link"/>
      </a>
    </span>
     </div>
  </xsl:template>

 

  <xsl:template match="image">
        <img style="width:300px; float:left; margin:10px;" src="{.}" alt="{.}"/>
      </xsl:template>

  <xsl:template match="opis">
    <br></br>
    <xsl:text> OPIS:</xsl:text>
     <br></br>
    <xsl:value-of select="."/>
  </xsl:template>


  
  

  <xsl:template match="usluga">
    <br/>
    <span style = "color:green;font-size:16pt">
      <xsl:if test="koszt>50">
       
      <xsl:value-of select ="concat(rodzaj,'   ')" />
     
      <xsl:value-of select = "concat(wykonawca/firma,'   ')" />
         
        <xsl:value-of select="format-number(koszt,'###.00 PLN')"/>
      
      </xsl:if>

    </span>
   
  </xsl:template>
  
<xsl:template match="usluga/wykonawca/numer">
 
<xsl:apply-templates select="kierunkowy"/>
  <xsl:value-of select="format-number(./number,'#########')"/>
  <br/>

</xsl:template>
  
<xsl:template match="kierunkowy">
 <xsl:choose>
  <xsl:when test="@znak">
    <xsl:if test="@znak='+'">
      <span style="color:blue">
       <xsl:value-of select="."/>
    </span>
   </xsl:if>
  <xsl:if test="@znak='-'">
  <span style="color:purple">
       <xsl:value-of select="."/>
    </span>
  </xsl:if>
 </xsl:when>
   <xsl:otherwise>

   <xsl:text> ???</xsl:text>
 </xsl:otherwise>
</xsl:choose>
 
</xsl:template>

</xsl:stylesheet>
