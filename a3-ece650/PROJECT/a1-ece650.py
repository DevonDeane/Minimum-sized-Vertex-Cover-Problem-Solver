import sys

import re
import hashlib
import math
import operator
from itertools import count

def distance(ptA, ptB):
  dx = ptA.x - ptB.x
  dy = ptA.y - ptB.y
  return math.hypot(dx,dy)

class Street(object):
    uid = -1
    # name = ''
    # points = []
    # strPoints = []
    # #pointsSet = set()
    # lines = []
    # strLines = []

    def __init__(self):
        #self.uid = 0
        #self.uid += 1
        #self.uid = uid
        self.name = ''
        self.points = []
        self.strPoints = []
        #pointsSet = set()
        self.lines = []
        self.strLines = []

        self.edges = []
        self.strEdges = []




    def setUid(self, uid):
        self.uid = uid

    def getUid(self):
        return self.uid

    def setName(self, newName):
        self.name = newName

    def getName(self):
        return self.name

    def addPoints(self, newPoint): # DANGER REVISIT
        if self.points:
            if str(newPoint) in self.points:
                pass
            else:
                for i in self.points:
                    x = str(i)
                    y = str(newPoint)
                    #if str(i) == str(newPoint):
                    if x == y:
                        continue#pass#return  # use return instead of break to leave the method body
                    else:
                        self.points.append(newPoint)
                        self.strPoints.append(str(newPoint))
        else:
            self.points.append(newPoint)
            self.strPoints.append(str(newPoint))
        #self.pointsSet.add(newPoints)

    def getPoints(self):
        return self.points

    def getStrPoints(self):
        return self.strPoints

    def addLines(self, newLine): # DANGER REVISIT
        if self.lines:
            for i in self.lines:
                if str(i) == str(newLine):
                    return  # use return instead of break to leave the method body
            self.lines.append(newLine)
            self.strLines.append(str(newLine))
        else:
            self.lines.append(newLine)
            self.strLines.append(str(newLine))
        #self.lines = newLines

    def getLines(self):
        return self.lines

    def getStrLines(self):
        return self.strLines



    def getEdges(self):
        return self.edges

    def getStrEdges(self):
        return self.strEdges


    # streetInfo = (uid, name, points, lines)

    # if passedName not in self.names:
    #   return streetInfo
    # else:
    #   name = self.streets[passedName]




    #   return streetInfo

        # #========================================
        # #  Access individual street lines
        # print streetName
        # for line in self.streets[streetName]:
        #   print line

        # #========================================  
        # #  Access dictionary list of street objects
        # print self.streets[streetName]

        # #========================================
        # #  Access all streets in streets dictionary
        # print self.streets

        # #========================================






class Map(object):
    # contains streets by name with corresponding points associated with streets
    streets = {}
    streetPoints = {}
    names = set()
    #vertices = set()

    streetObjs = []
    intersectObjs = []
    intersectCouples = []

    # Update
    newEdges = {}

    def __init__(self):
        #  used to initialize street dictionary if necessary
        #self.streets = {}
        pass

    # def getNewEdges(self):
    #     return self.newEdges


    def getNames(self):
        return self.names

    # def street(self,passedName):
    #   uid = -1
    #   name = ''
    #   points = []
    #   lines = []

    #   streetInfo = (uid, name, points, lines)

    #   if passedName not in self.names:
    #     return streetInfo
    #   else:
    #     name = self.streets[passedName]




    #     return streetInfo

    #     # #========================================
    #     # #  Access individual street lines
    #     # print streetName
    #     # for line in self.streets[streetName]:
    #     #   print line

    #     # #========================================  
    #     # #  Access dictionary list of street objects
    #     # print self.streets[streetName]

    #     # #========================================
    #     # #  Access all streets in streets dictionary
    #     # print self.streets

    #     # #========================================


    def uniqueStreet(self, name):

        #  Case insensitive check
        for curName in self.names:
            lowername = curName.lower()
            if name.lower() == lowername:
                return False

        #  Name existence check
        if name not in self.names:
            self.names.add(name)
            return True
        else:
            return False

    def removeStreet(self,streetName):
      message = ''
      if streetName.lower() not in self.names:
        message = 'Error: This street does not presently exist!'
        return message
      else:
        # remove name from self.names (set)
        self.names.remove(streetName)
        # remove name from self.streets (dict)
        del self.streets[streetName]
        # remove from intersectCouples (n/a w/new implementa)
        for streetObj in self.streetObjs: # which is a list
          if streetObj.getName() == streetName:
            self.streetObjs.remove(streetObj)
            #message = 'Street deleted.'
            return




    def addStreet(self,path,streetName):
            # note, the reality is that Weber Street is made up of many individual lines. Order does not matter when it comes to lines existence
        # it is fair to assume that coordinates are given in order of their respective lines

        # for point in path:
        #   line = 

        # # Old implementation (working but wrong idea)
        # count = 0
        # lineList = []
        # line = []
        # for location in path:
        #   if count != 2:
        #     cord = re.findall(r'[+-]?\d{1,}',location)
        #     #print findCor #  list of two coordinates that make a point
        #     line.append(cord)
        #     print line,'line'
        #     count += 1
        #   if count == 2:
        #     count = 0
        #     lineList.append(line)
        #     line = []
        #     print lineList,'lineList'

        #  New and Improved Add Street Implementation 
        #  This should be a def (function) by the way

        #print '\n\n\n',path,'path\n\n\n'
        #  STREET OBJECT CREATION
        street = Street()

        #  STREET NAME DECLARATION    # DONE
        street.setName(streetName)

        # #  STREET POINTS APPENDED     # DONE
        # street.addPoints()

        # #  STREET LINES APPENDED      # DONE
        # street.addLines()

        count = 0
        streetLine = []
        line = []
        for location in path:
            if count != 2:
                cord = re.findall(r'[+-]?\d{1,}',location)
                #  list of two values that make one point
                #  cord therefore is a point
                line.append(cord)
                #print line,'line'
                count += 1
            if count == 2 and len(line)>1:
                count = 1
                streetLine.append(line)

                lastPoint = line[1] 
                line = [lastPoint]
                #print streetLine,'streetLine'

        #print streetLine,'streetLineFinal'  # where streetLine is the actual street (group of connected lines)

        #  To do today:
        # make point objects then line objects then find intersects then add intersects to dictionary of vertices then remove lines not intersecting in dict of vertices and recreate lines based on new intersections etc. etc. Trust God.

        #  Point Converter

        streetLineObjs = []
        streetPointObjs = []
        pointFilter = []  #     Quite useless

        setA = set()
        ptFilter = []
        #ptFilter.append(0)
        
        ptList = []
        for line in streetLine:
            ptList = []
            for point in line:
                digits = 0
                vals = []
                #ptCounter = 0
                for value in point:
                    value = int(value)
                    vals.append(value)
                    digits += 1
                if digits == 2 and len(vals) > 1:
                    pt = Point(vals[0],vals[1])
                    pt.setStreetName(streetName)
                    
                    
                    #  Removes duplicates successfully
                    strPt = str(pt)

                    if strPt not in setA:
                      setA.add(strPt)
                      ptFilter.append(pt)          

                    
                    
                    
                    
                              
                    


                    ptList.append(pt)
                    #  STREET POINTS DECLARATION
                    point = str(pt)
                    #if point not in pointFilter:
                    pointFilter.append(pt)
                    street.addPoints(pt)
                    #  =========================
                    #  IMPORTANT (POINTS)
                    streetPointObjs.append(pt)
                    #  =========================
                    #ptCounter +=1

                # #  REWORK =====================================
                # if len(ptList) == 2:  # ptCounter == 2:
                #     segment = Line(ptList[0], ptList[1])
                #     streetLineObjs.append(segment)
                # #  REWORK =====================================

                #  WHAT WE WANT IS TO MAKE LINES FROM POINTS
                #  APPEND POINTS TO streetLineObjs

                
                


                #print
                for pt in ptList:
                  #print pt,'__pt in ptList__'
                  pass
                #print

        for pi in ptFilter:
          #print pi,'____pi______'
          pass

        for i in range(0,len(ptFilter)-1):
          #print i,'___i_____'
          segment = Line(ptFilter[i], ptFilter[i+1])
          segment.setStreetName(streetName)
          streetLineObjs.append(segment)

        #print
        if ptList:
          for pt in ptList:
            #print pt,'__pt in ptList<FINAL>__'
            pass
          #print

        #print
        #print ptFilter
        for pt in ptFilter:
          #print str(pt),'__pt in ptFilter<NEW>__'
          pass
        #print

        #print street.getStrPoints(), '__street.getStrPoints()__'

        #print streetPointObjs,'__streetPointObjs__'
        for point in streetPointObjs:
            #print point,'__point__'
            pass

        strPointObjs = []
        for i in streetPointObjs:
            string = str(i)
            if string not in strPointObjs:
                strPointObjs.append(str(i))
                #print i,'__i__'

        #print strPointObjs,'__strPointObjs__'
        for newpoint in strPointObjs:
            #print newpoint,'__newpoint__'
            pass
# #  STREET POINTS DECLARATION
#     for point in ptList:
#       street.addPoints(point)
# #  =========================

        # street = {}

        # street[streetName] = streetLineObjs

        # print street[streetName]


        #  Working code below (~6 lines)
        #  Warning, the line below points to the original stLObjs list
        # streetName = streetLineObjs

        # print streetName
        # for lineSeg in streetName:
        #   print lineSeg


        #  Goal

        # thisdict["secondval"] = ["2ndval", "3rdval"] #some values in the list

        streetLines = []

        for lineSeg in streetLineObjs:
            streetLines.append(lineSeg)

        #streetPoints = []


        # WAS HERE!

        # i=0
        # for point in streetPointObjs:
        #   #streetPoints.append(point)
        #   self.streetPoints[i] = str(point)
        #   i += 1 




        #print streetLines,'_streetLines_'

        #streetName = str(streetName)
        #  Even more effective than line above is line below
        #name = streetName

        #print name


        #  In order to see street lines do the following
        visualStreet = []
        for line in streetLines:
            visualStreet.append(str(line))
        #print visualStreet

        self.streets[streetName] = streetLines  #02


        #self.streets[streetName] = streetPoints

        #print ''
        #print streetName
        #==========IMPORTANT CODE BELOW==========

        #  Access individual street lines      #02
        for line in self.streets[streetName]:
            #  STREET LINES APPENDED
            street.addLines(line)
            #print line,'___line___' #remove when serious


        # i = 0
        # for point in self.pointsDict[i]:
        #   #  STREET LINES APPENDED
        #   street.addLines(line)
        #   print line,'___line___' #remove when serious




        #print street.getLines()
        
        #  FILTER BELOW BEFORE APPENDING
        #print street,'__street__'
        self.streetObjs.append(street)
        #=========================================



        #========================================  
        #  Access dictionary list of street objects
        #print self.streets[streetName]

        #print self.streetPoints, '__streetPoints__'

        #========================================
        #  Access all streets in streets dictionary
        #print self.streets

        #========================================


    # def updateVertices(self):

    #   #vertice = {}

    #   for street in self.streets:
    #     for vertex in street:
    #       self.vertices.add(vertex)



    def graph(self):
        #  Vertices


        # Replaced with below
        # sys.stdout.write('V = {\n')

        sys.stdout.write('V ')
        sys.stdout.flush()

        self.vertices()

        # Replaced with below
        # sys.stdout.write('}\n')

        sys.stdout.write('\n')
        sys.stdout.flush()

        # Replaced with below
        # sys.stdout.write('E = {\n')

        sys.stdout.write('E {')
        sys.stdout.flush()

        self.edges()

        sys.stdout.write('}\n')
        sys.stdout.flush()

    def vertices(self):

        # Add vertices which are intersections
        #++++++++++++++++++++++++++++++++++++++++++++

        # if self.intersectCouples:
        #   for couple in self.intersectCouples:
        #     self.intersectCouples.remove(couple)

        self.intersectCouples[:] = []

        # Collect intersections
        intersectObjs = []
        intersectSet = set()

        allLines = []
        
        # intersectCouples = []
        intersectCouple = []

        streets = 0

        for street in self.streetObjs:
          lines = street.getLines()
          for line in lines:
            allLines.append(line)#street.getLines())
        #print str(allLines),'\n'

        # position = 0
        # for line in allLines:
        
        for i in range(len(allLines)):
          for j in range(i + 1, len(allLines)):
              #if Intersect(allLines[i], allLines[j])

              #print allLines[i]
              #print allLines[j]

              met = Intersect (allLines[i], allLines[j])
              if not met:
                #print 'some'
                #print 'NOT MET'  # Accurately prints not met
                pass
              else:
                #print 'somesome'
                intersectCouple.append(allLines[i])
                intersectCouple.append(allLines[j])
                intersectCouple.append(met)

                self.intersectCouples.append(intersectCouple)

                intersectCouple = list()

                strMet = str(met)
                if strMet not in intersectSet:
                  intersectSet.add(str(met))
                  intersectObjs.append(met)
                #print self.intersectCouples,'intersectCouples'

        #print intersectObjs,'___intersectObjs___\n\n\n'
        for obj in intersectObjs:
          #print str(obj),'___intersectObjs___\n\n'
          #print obj.uid,'___obj.uid___\n'

          # Important Line
          #vert[obj.uid] = str(obj)
          pass

        #++++++++++++++++++++++++++++++++++++++++++++
        # ABOVE IS CRITICAL











        vert = {}
        filterList = []

        # IMPLEMENTATION A
        #==================================================
        # for street in self.streetObjs:
        #     points = street.getPoints() #
        #     #print points,'__points__'
        #     for point in points:
        #         if str(point) not in filterList:
        #             filterList.append(str(point))
        #             vert[point.uid] = str(point)
        #             #print point.uid, '__point.uid__'
        #             #print point.getUid(),'__point.getUid()__'

        # # print vert, '__vert__'
        # # print
        #==================================================

        # IMPLEMENTATION B
        #==================================================
        
        # Utilize self.intersectionCouples

        #vertexPts = []
        for couple in self.intersectCouples:
          #couple(list)containing line A, line B, intersection
          for obj in couple:
            if type(obj) is Line:
              linePtsList = list(obj.getLPointObjs())
              if linePtsList and len(linePtsList)>1:
                #vertexPts.append(linePtsList[0])
                vert[linePtsList[0].uid] = str(linePtsList[0])
                #vertexPts.append(linePtsList[1])
                vert[linePtsList[1].uid] = str(linePtsList[1])
            if type(obj) is Point: # Therefore intersection
              #vertexPts.append(obj) 
              vert[obj.uid] = str(obj)

        #===================================================
        eachRegLine = []
        for street in self.streetObjs:
          lines = street.getLines()
          for line in lines:
            eachRegLine.append(line)

        # for lineX in eachRegLine:
        #   print lineX
        # for i in listOfInters:
        #   print i
        # print listOfInters
        # print listOfLines
        for lineX in eachRegLine:
          points = list(lineX.getLPointObjs())
          for lineY in eachRegLine:
            nxtPoints = list(lineY.getLPointObjs())
            if str(lineX) == str(lineY):
              continue
            else: 
              if len(points) > 1:
                if PointIntersect(lineY,points[0]) and PointIntersect(lineY, points[1])and len(points) > 1:
                  #listOfInters.append(points[0])
                  #listOfInters.append(points[1])
                  #listOfLines.append(lineX)
                  #listOfLines.append(lineY)

                  # add points of lineX
                  vert[points[0].uid] = str(points[0])
                  vert[points[1].uid] = str(points[1])
                  # add points of lineY
                  if len(nxtPoints) > 1:
                    vert[nxtPoints[0].uid] = str(nxtPoints[0])
                    vert[nxtPoints[1].uid] = str(nxtPoints[1])
                  #print ('found something')

        # for l in listOfLines:
        #   print l

        #===================================================




        #==================================================
        counter = 0
        newListVert = []
        newVerts = 0
        newVert = []
        for x in vert:
          newListVert.append(vert[x])
        

        # newdict = {}
        vIndex = 0

        # if (self.newEdges):
        #   self.newEdges.clear()
        # else:
        for x in vert:
          # print x
          
          
          # newdict[vIndex] = x
          self.newEdges[vIndex] = x
          vIndex += 1


        # print self.newEdges
        
        # for i in range(0,len(newListVert)):
        #   thisdict[i] = "red"

        # print vert


        # for x in newListVert:
        #   print x
          
        # print len(newListVert)

        for i in range(0,len(newListVert)):
          newVert.append(i)

        # print "\n"
        # for x in newVert:
        #   print x
        # print "\n"

        # WORKING WITH newVert

        for key in vert:
            #print "key: %s , value: %s" % (key, vert[key])
            counter +=1;

            # print ' ', key, ':', vert[key]

            # Replaced with below
            # sys.stdout.write('  ')
            # sys.stdout.write(key)
            # sys.stdout.write(' : ')
            # sys.stdout.write(vert[key]+'\n')

            

            # sys.stdout.write('\n')
        sys.stdout.write(str(counter))
        sys.stdout.flush()




    def edges(self):
          edges = []
          edgesSet = set()

          # Update
          strings = []

          listOfLines = []
          listOfInters = []
          setOfLines = set() #strings
          setOfInters = set() #strings
          for couple in self.intersectCouples:
            #couple(list)containing line A, line B, intersection
            for obj in couple:
              if type(obj) is Line:
                #if str(obj) not in setOfLines:
                if obj.getUid() not in setOfLines:
                  #setOfLines.add(str(obj))
                  setOfLines.add(obj.getUid())
                  listOfLines.append(obj)
              if type(obj) is Point:
                if obj.getUid() not in setOfInters:
                  setOfInters.add(obj.getUid())
                  listOfInters.append(obj)

          # for line in listOfLines:
          #   print line

          # for inter in listOfInters:
          #   print inter

          # Special Case 2 Provision Goes Here
          # IMPLEMENTATION 2 N.B. NOT WORKING
          # for i in range(len(listOfLines)):
          #   for j in range(i + 1, len(listOfLines)):
          #     points = list(listOfLines[i].getLPointObjs())
          #     if len(points) > 1:
          #       if PointIntersect(listOfLines[j],points[0]) and PointIntersect(listOfLines[j], points[1]) and IsIn(listOfLines[i],listOfLines[j]):
          #         #print 'We have what could be the solution'
          #         if points[0].getUid() not in setOfInters:
          #           setOfInters.add(points[0].getUid())
          #           listOfInters.append(points[0])
          #         if points[1].getUid() not in setOfInters:
          #           setOfInters.add(points[1].getUid())
          #           listOfInters.append(points[1])
                  



              # met = Intersect (allLines[i], allLines[j])
              # if not met:
              #   #print 'some'
              #   #print 'NOT MET'  # Accurately prints not met
              #   pass

          # IMPLEMENTATION 1
          # for line in listOfLines:
          #   points = list(line.getLPointObjs())
          #   if len(points) > 1:
          #     if PointIntersect(line,points[0]) and PointIntersect(line, points[1]):
          #       print 'We have what could be the solution'

          eachRegLine = []
          for street in self.streetObjs:
            lines = street.getLines()
            for line in lines:
              eachRegLine.append(line)

          # for lineX in eachRegLine:
          #   print lineX
          # for i in listOfInters:
          #   print i
          # print listOfInters
          # print listOfLines


          # ISSUE CODE, SUGGESTION, FIX INTERSECT #
          
          listOfLinesSetFilter = set()
          for i in listOfLines:
            if str(i) not in listOfLinesSetFilter:
              listOfLinesSetFilter.add(str(i))


          for lineX in eachRegLine:
            points = list(lineX.getLPointObjs())
            for lineY in eachRegLine:
              if str(lineX) == str(lineY):
                continue
              else: 
                if len(points) > 1:
                  if PointIntersect(lineY,points[0]) and PointIntersect(lineY, points[1]) and len(points) > 1:
                    listOfInters.append(points[0])
                    # print lineX, 'LINEX'
                    # print lineY, 'LINEY'
                    # print points[0], 'inter'
                    # print points[1], 'inter'
                    listOfInters.append(points[1])
                    if str(lineX) not in listOfLinesSetFilter:
                      listOfLinesSetFilter.add(str(lineX))
                      #listOfLines.append(lineX)
                    #print
                    # print lineX,'lineX'
                    if str(lineY) not in listOfLinesSetFilter:
                      listOfLinesSetFilter.add(str(lineY))
                      listOfLines.append(lineY)
                    # print lineY, 'lineY'
                    #print
                    # print ('found something')

          # ISSUE CODE, SUGGESTION, FIX INTERSECT #

          # print
          # for l in listOfLines:
          #   print l
          # print

          # print 'inters'
          # for i in listOfInters:
          #   print i
          # print 'inters'
          # for i in listOfInters:
          #   print i
          # print listOfInters
          #try gathering from listOfLines' source

          # so far so good thanks to God
          
          listOfFilteredLines = listOfLines
          for line in listOfLines:
            lineIntersections = []
            setOfLineIntersections = set()
            for inter in listOfInters:
              if PointIntersect(line,inter):
                #if inter.getUid() not in setOfLineIntersections:
                if str(inter) not in setOfLineIntersections:
                  #setOfLineIntersections.add(inter.getUid())
                  setOfLineIntersections.add(str(inter))
                  lineIntersections.append(inter)
                  #print inter,'inter'
            #setOfLineIntersections = set()
            # for inters in lineIntersections:
            #   print inters, '__inter__'

            

            # rest of code here
            keyLine = line

            # paste code block here (for inters)
            points = list(keyLine.getLPointObjs())
            if len(points)>1:
              keyLineX = points[0]
              keyLineY = points[1]

            inters = lineIntersections

            
            
            #  input requires inters
            #==============================

            #order inters by distance from keyLineX
          # Note: Already have a list of inters called 'inters' 
            orderedInters = []
            interDistances = []
            # for inter in inters:
            #   interDistance = []
            #   dist = distance(keyLineX, inter)
            #   interDistance.append(inter)
            #   interDistance.append(dist)
            #   interDistances.append(interDistance)

            #for i in range(1,inters):
            distanceKeeper2 = {}
            for inter in inters:
              dist = distance(keyLineX, inter)
              # distanceKeeper =    {
              #   str(inter): inter,
              #   "distance": dist,

              # }
              distanceKeeper2[inter] = dist
            #interDistances.append(distanceKeeper2)
            # print distanceKeeper2

            #  Sort keys by value
            results = []

            x = distanceKeeper2
            sorted_x = sorted(x.items(), key=operator.itemgetter(1))

            for x in sorted_x:
              listed = list(x)
              results.append(listed)

            # print results

            for result in results:
              if len(result) > 1:
                orderedInters.append(result[0])
            # print orderedInters,'\n\n\n'

            # inters are now ordered Hallelujah!

            # create ordered line list

            orderedPointList = []
            orderedPointList.append(keyLineX)
            for inter in orderedInters:
              orderedPointList.append(inter)
            orderedPointList.append(keyLineY)

            # print orderedPointList, 'orderedPointList'

            # newLinesList = []
            # newPts = []
            # digits = 0
            # for point in orderedPointList:
            #   newPts.append(point)
            #   digits += 1
            #   if digits == 2:
            #     if len(newPts) > 1:
            #       line = Line(newPts[0],newPts[1])

            #       digits = 0
            #       newPts = list()
            #       newLinesList.append(line)
            
            # print newLinesList, 'here'

            count = 0
            newLines = []
            points = []
            for location in orderedPointList:
                if count != 2:
                    #cord = re.findall(r'[+-]?\d{1,}',location)
                    #  list of two values that make one point
                    #  cord therefore is a point
                    points.append(location)
                    #print line,'line'
                    count += 1
                if count == 2:
                    count = 1
                    #newLines.append(points)
                    if len(points) > 1:
                      newLines.append(Line(points[0],points[1]))
                    if len(points) > 1:
                      lastPoint = points[1] 
                    points = [lastPoint]

            # if keyLine
            # print newLines, 'newLines'

            # for line in newLines:
            #   print line
            # print


            #==============================
            #  outputs newLines (list)


          # ============================
          # append to edge list here
          # ============================
          
            for line in newLines:
              if str(line) not in edgesSet:
                points = line.getLPointObjs()
                if len(points) > 1:
                  if not (points[0] is points[1]) and str(points[0]) != str(points[1]):
                    # print str(points[0])
                    # print points[1],'\n'
                    edgesSet.add(str(line)) 
                    l = line.getLPointObjs()
                    length = len(self.newEdges)
                    index = 0
                    edge = []
                    # del edge[:]
                    for i in self.newEdges:
                      # edge.clear()
                      
                      # print self.newEdges[i]
                      # print i
                      if l[0].getUid() == self.newEdges[i]:
                        # print l[0].getUid()
                        edge.append(i)
                      if l[1].getUid() == self.newEdges[i]:
                        # print l[1].getUid()
                        edge.append(i)
                        # edge.append(self.newEd)
                    string = "<" + str(edge[0]) + "," + str(edge[1]) + ">"
                    # print string
                    # edges.append(string)
                    strings.append(string)
                    # edges.append(line.getEdge())
                    # Remove below
                    # edges.append(edge)


            #listOfLines.remove(keyLine)

          # order inters on according to line


          # for line in listOfLines:
          #   lineX = line
          #   listOfLines.remove(line)
          #   if lineX



          # # add intersections to merged couple
          # pointUidSet = set ()
          # for couple in filIntersectCouples:
          #   for item in couple:
          #     if type(item) is Point:
          #       #if item not in mergedCouple:
          #       if item.getUid() not in pointUidSet:
          #         pointUidSet.add(item.getUid())
          #         mergedCouple.append(item) 
          #         inters.append(item)
        
          # edge = [] # place this above code upper


          #======================================
          # append to edge list here
          #======================================


          # IMPLEMENTATION A
          # for street in self.streetObjs:
          #     lines = street.getLines()
          #     for line in lines:
          #         #  REDO IMPLEMENTATION OF POINT UIDS. CANNOT BE SET EVERYTIME A POINT IS MADE. SHOULD BE SET AFTER POINT IS FILTERED
          #         #print line,'__line__'
          #         edge.append(line.getEdge())
          
          #+++++++++++++++++++++++++++++++++++++++++++++++++++





          # IMPLEMENTATION B
          # Utilize intersectCouples and .getEdge() for lines
          # Append edges to edge list

          # intersection = []
          # for couple in self.intersectCouples:
          #   #couple(list)containing line A, line B, intersection
          #   for obj in couple:
          #     if type(obj) is Point:
          #       intersection.append(obj)
                
                

          # for couple in self.intersectCouples:
          #   #couple(list)containing line A, line B, intersection
          #   for obj in couple:
          #     if type(obj) is Line:
          #       linePtsList = list(obj.getLPointObjs())
                
          #       if linePtsList and intersection:
          #         lineA1 = Line(linePtsList[0], intersection[0])
          #         lineA2 = Line(intersection[0], linePtsList[1]) 
          #         edgeA1 = lineA1.getEdge()
          #         edgeA2 = lineA2.getEdge()
          #         # print lineA1,'lineA1'
          #         # print edgeA1,'edgeA1'
          #         # print lineA2,'lineA2'
          #         # print edgeA2,'edgeA2'
          #         edge.append(edgeA1)
          #         edge.append(edgeA2)

          
          # # IMPLEMENTATION A
          # # for ed in edge:
          # #   print ' ',ed ,', '

          # # IMPLEMENTATION B
          # for i in range (0, len(edge)):
          #   if i != len(edge)-1:
          #     print ' ',edge[i] ,', '
          #   else:
          #     print ' ',edge[i]


          # Replace with below
          # for i in range (0, len(edges)):
          #   if i != len(edges)-1:
          #     # print ' ',edges[i] ,', '
          #     sys.stdout.write('  ')
          #     sys.stdout.write(edges[i])
          #     sys.stdout.write(' ,  \n')
          #   else:
          #     # print ' ',edges[i]

          #     sys.stdout.write('  ')
          #     sys.stdout.write(edges[i]+'\n')

          # UNDER CONSTRUCT
          # =================================================
          # thisdict = {}

          # # Dictionary loader
          # for i in range (0, len(edges)):
          #     thisdict[i] = edges[i]

          # # print thisdict # actual line of code

          # # for x in thisdict:
          # #   print(x)
          # for i in range (0, len(strings)):
          #   if i != len(strings)-1:
          #     # print ' ',edges[i] ,', '
          #     # sys.stdout.write('  ')
          #     sys.stdout.write(strings[i])
          #     sys.stdout.write(',')
          #   else:
          #     # print ' ',edges[i]

          #     # sys.stdout.write('  ')
          #     sys.stdout.write(strings[i])

          # =================================================

          # thisdict = {}

          # # Dictionary loader
          # for i in range (0, len(s)):
          #     thisdict[i] = edges[i]

          # print thisdict # actual line of code

          # for x in thisdict:
          #   print(x)
          # for i in range (0, len(strings)):
          #   if i != len(strings)-1:
          #     # print ' ',edges[i] ,', '
          #     # sys.stdout.write('  ')
          #     sys.stdout.write(strings[i])
          #     sys.stdout.write(',')
          #   else:
          #     # print ' ',edges[i]

          #     # sys.stdout.write('  ')
          #     sys.stdout.write(strings[i])

          # for i in strings:
          #   print i

          for i in range (0, len(strings)):
            if i != len(strings)-1:
              # print ' ',edges[i] ,', '
              # sys.stdout.write('  ')
              sys.stdout.write(strings[i])
              sys.stdout.flush()
              sys.stdout.write(',')
              sys.stdout.flush()
            else:
              # print ' ',edges[i]

              # sys.stdout.write('  ')
              sys.stdout.write(strings[i])
              sys.stdout.flush()
            

          # USEFUL
          # for i in range (0, len(edges)):
          #   if i != len(edges)-1:
          #     # print ' ',edges[i] ,', '
          #     # sys.stdout.write('  ')
          #     sys.stdout.write(edges[i])
          #     sys.stdout.write(',')
          #   else:
          #     # print ' ',edges[i]

          #     # sys.stdout.write('  ')
          #     sys.stdout.write(edges[i])

          # Load up into a dictionary and print keys instead of values
              


          # # YOU ARE HERE, ISSUE IS THAT YOUR notICES AND EDGES ARE BASED ON ORIGINALLY CREATED VERTICES AND EDGES. EVERYTHING SHOULD BE GIVEN BIRTH TO FROM STREETOBJS INSTEAD!

          # #  PRINT STREETOBJS content to get to the bottom of this


          # print self.streetObjs, '__streetObjs__'

          # for street in self.streetObjs:
          #     print street,'__street in streetObjs__'
          #     lines = street.getLines()
          #     for line in lines:
          #         print line,'__line in lines__'
          #         print line.getEdge(),'__line.getEdge()__'  # Problem here

          #         #  Get edge does not return appropriate point ids
          # # def vertices(self):
          # #   vert = {}

          # #   for street in self.streetObjs:
          # #     points = street.getStrPoints() #
          # #     for point in points:
          # #       vert[point.uid] = point




          #     # for street in self.streetObjs:
          #     #   vert[streetObj.point.uid] = streetObj.point








def pp(x):
    """Returns a pretty-print string representation of a number.
       A float number is represented by an integer, if it is whole,
       and up to two decimal places if it isn't
    """
    if isinstance(x, float):
        if x.is_integer():
            return str(int(x))
        else:
            return "{0:.2f}".format(x)
    return str(x)

class Point(object):
    """A point in a two dimensional space"""
    uids = count(0)
    streetName = ''

    def __init__(self, x, y):
        
        self.x = float(x)
        self.y = float(y)
        
        #self.uid = hash('(' + pp(self.x) + ', ' + pp(self.y) + ')')
        #self.uid = next(self.uids) 
        self.uid = hashlib.sha256('(' + pp(self.x) + ', ' + pp(self.y) + ')'.encode("UTF-8")).hexdigest()[:6]



    def getUid(self):
        return self.uid


    def getStreetName(self):
      return self.streetName

    def setStreetName(self, streetName):
      self.streetName = streetName.lower()

    def __str__(self):  # __repr__
        return '(' + pp(self.x) + ', ' + pp(self.y) + ')'


class Line(object):

    streetName = ''

    """A line between two points"""
    def __init__(self, src, dst):
        self.src = src
        self.dst = dst
        
        self.uid = hashlib.sha256('['+ str(self.src) + '-->' + str(self.dst) + ']'.encode("UTF-8")).hexdigest()[:5]

    # def points(self):  # __repr__
    #     return '(' + pp(self.src) + ', ' + pp(self.dst) + ')'

    #  Under Construction
    def getEdge(self):
        return '<'+ str(self.src.getUid()) + ',' + str(self.dst.getUid()) + '>' 

    def getLPointObjs(self):
        return self.src, self.dst  

    def getUid(self):
        return self.uid

    def getStreetName(self):
      return self.streetName

    def setStreetName(self, streetName):
      self.streetName = streetName.lower()

    def __str__(self):  # __repr__
        return '['+ str(self.src) + '-->' + str(self.dst) + ']'



def Intersect (l1, l2):
    """Returns a point at which two lines intersect"""

    if len(l1.getStreetName()) > 0 and len(l2.getStreetName()) > 0:
      if l1.getStreetName() == l2.getStreetName():
        return
    # uids = count(10000)
    # uid = ''

    # # def __init__(self):
    # #     self.uid = next(self.uids)
        

    x1, y1 = l1.src.x, l1.src.y  # x = src, y = dst of one line
    x2, y2 = l1.dst.x, l1.dst.y

    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))

    # Implementation A
    # if xden == 0:
    #   #xcoor = 0
    #   #return
    # else:
    #   xcoor =  xnum / xden

    # Implementation B
    try:
      xcoor = xnum / xden
    except ZeroDivisionError:
      xcoor = 0 # instead work as if the slopes are equal
      #return True
      # either line on line or two lines meet
      # reuse code to check which is the case

      # then split lines accordingly

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)

    # Implementation A
    # if yden == 0:
    #   return
    # else:
    #   ycoor = ynum / yden

    # Implementation B
    try:
      ycoor = ynum / yden
    except ZeroDivisionError:
      ycoor = 0 # instead work as if the slopes are equal



    startXA = 0
    startXB = 0

    startYA = 0
    startYB = 0

    # print x1, '_x1_'
    # print x2, '_x2_'
    # print xcoor, '_xcoor_'
    # print ycoor, '_ycoor_'
    # Check if intersection is contained on Line1
    if x1 < x2:
      startXA = x1
      endXA = x2
    elif x2 < x1:
      startXA = x2
      endXA = x1
    else: # if they are equal
      if y1 < y2:
        startXA = x1
        endXA = x2
      elif y1 > y2:
        startXA = x2
        endXA = x1
      else:
        # not a line, this should never occur, but to be safe, return
        return

    
    if y1 < y2:
      startYA = y1
      endYA = y2
    elif y2 < y1:
      startYA = y2
      endYA = y1
    else: # if they are equal
      if x1 < x2:
        startYA = y1
        endYA = y2
      elif x2 < x1:
        startYA = y2
        endYA = y1
      else:
        # not a line, this should never occur, but to be safe, return
        return


    # AND

    if x3 < x4:
      startXB = x3
      endXB = x4
    elif x4 < x3:
      startXB = x4
      endXB = x3
    else: # if they are equal
      if y3 < y4:
        startXB = x3
        endXB = x4
      elif y4 > y3:
        startXB = x4
        endXB = x3
      else:
        # not a line, this should never occur, but to be safe, return
        return

    # x3 and x4 cannot be equal otherwise they are not a line
    if y3 < y4:
      startYB = y3
      endYB = y4
    elif y4 < y3:
      startYB = y4
      endYB = y3
    else: # if they are equal
      if x3 < x4:
        startYB = y3
        endYB = y4
      elif x4 < x3:
        startYB = y4
        endYB = y3
      else:
        # not a line, this should never occur, but to be safe, return
        return


    # if xcoor == 0 and ycoor == 0:
    #   return Point(xcoor, ycoor)
    #   print 'landed'
    # elif xcoor == 0:
    #   print 'landed3'
    #   print Point(xcoor, ycoor)
    #   return Point(xcoor, ycoor)
    # elif ycoor == 0:
    #   print 'landed4'
    # else:
    #   print 'landed2'
    #   return

    if xcoor == 0 or ycoor == 0:
       if not (xcoor == 0 and ycoor == 0): 
          return Point(xcoor, ycoor)


    if xcoor >= startXA and xcoor <= endXA:
      if ycoor >= startYA and ycoor <= endYA:

        if xcoor >= startXB and xcoor <= endXB:
          if ycoor >= startYB and ycoor <= endYB:

            return Point(xcoor, ycoor)
    else:
      return
    # elif xcoor == 0 or ycoor == 0:
    #   return Point(xcoor, ycoor)
    # else:
    #   return

def IsIn (l1, l2):
    """Returns a point at which two lines intersect"""

    # uids = count(10000)
    # uid = ''

    # # def __init__(self):
    # #     self.uid = next(self.uids)
        

    x1, y1 = l1.src.x, l1.src.y  # x = src, y = dst of one line
    x2, y2 = l1.dst.x, l1.dst.y

    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
    xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))

    # Implementation A
    # if xden == 0:
    #   #xcoor = 0
    #   #return
    # else:
    #   xcoor =  xnum / xden

    # Implementation B
    try:
      xcoor = xnum / xden
    except ZeroDivisionError:
      #xcoor = 0 # instead work as if the slopes are equal
      return True
      # either line on line or two lines meet
      # reuse code to check which is the case

      # then split lines accordingly

    ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
    yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)

    # Implementation A
    # if yden == 0:
    #   return
    # else:
    #   ycoor = ynum / yden

    # Implementation B
    try:
      ycoor = ynum / yden
    except ZeroDivisionError:
      ycoor = 0 # instead work as if the slopes are equal



    startXA = 0
    startXB = 0

    startYA = 0
    startYB = 0

    # print x1, '_x1_'
    # print x2, '_x2_'
    # print xcoor, '_xcoor_'
    # print ycoor, '_ycoor_'
    # Check if intersection is contained on Line1
    if x1 < x2:
      startXA = x1
      endXA = x2
    elif x2 < x1:
      startXA = x2
      endXA = x1
    else: # if they are equal
      if y1 < y2:
        startXA = x1
        endXA = x2
      elif y1 > y2:
        startXA = x2
        endXA = x1
      else:
        # not a line, this should never occur, but to be safe, return
        return

    
    if y1 < y2:
      startYA = y1
      endYA = y2
    elif y2 < y1:
      startYA = y2
      endYA = y1
    else: # if they are equal
      if x1 < x2:
        startYA = y1
        endYA = y2
      elif x2 < x1:
        startYA = y2
        endYA = y1
      else:
        # not a line, this should never occur, but to be safe, return
        return


    # AND

    if x3 < x4:
      startXB = x3
      endXB = x4
    elif x4 < x3:
      startXB = x4
      endXB = x3
    else: # if they are equal
      if y3 < y4:
        startXB = x3
        endXB = x4
      elif y4 > y3:
        startXB = x4
        endXB = x3
      else:
        # not a line, this should never occur, but to be safe, return
        return

    # x3 and x4 cannot be equal otherwise they are not a line
    if y3 < y4:
      startYB = y3
      endYB = y4
    elif y4 < y3:
      startYB = y4
      endYB = y3
    else: # if they are equal
      if x3 < x4:
        startYB = y3
        endYB = y4
      elif x4 < x3:
        startYB = y4
        endYB = y3
      else:
        # not a line, this should never occur, but to be safe, return
        return


    # if xcoor == 0 and ycoor == 0:
    #   return Point(xcoor, ycoor)
    #   print 'landed'
    # elif xcoor == 0:
    #   print 'landed3'
    #   print Point(xcoor, ycoor)
    #   return Point(xcoor, ycoor)
    # elif ycoor == 0:
    #   print 'landed4'
    # else:
    #   print 'landed2'
    #   return

    if xcoor == 0 or ycoor == 0:
      if not (xcoor == 0 and ycoor == 0): 
          return Point(xcoor, ycoor)


    if xcoor >= startXA and xcoor <= endXA:
      if ycoor >= startYA and ycoor <= endYA:

        if xcoor >= startXB and xcoor <= endXB:
          if ycoor >= startYB and ycoor <= endYB:

            return Point(xcoor, ycoor)
    else:
      return
    # elif xcoor == 0 or ycoor == 0:
    #   return Point(xcoor, ycoor)
    # else:
    #   return  

    #return Point(xcoor, ycoor)

    # def __init__(self):
    #     #self.uid = next(self.uids)
    #     self.uid = hash(str(Point(xcoor, ycoor)))
def PointIntersect (l1, p1):
    """Returns whether or not a point is in a line"""
    
    if len(l1.getStreetName()) > 0 and len(p1.getStreetName()) > 0:
      if l1.getStreetName() == p1.getStreetName():
        return False


    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y

    xcoor = p1.x
    ycoor = p1.y
    #===============================
    # IMPLEMENTATION B

    ax = l1.src.x
    ay = l1.src.y

    bx = l1.dst.x
    by = l1.dst.y

    cx = p1.x
    cy = p1.y 

    crossproduct = (cy - ay) * (bx - ax) - (cx - ax) * (by - ay)

    # compare versus epsilon for floating point values, or != 0 if using integers
    if abs(crossproduct) != 0 :#> epsilon:
        return False

    dotproduct = (cx - ax) * (bx - ax) + (cy - ay)*(by - ay)
    if dotproduct < 0:
        return False

    squaredlengthba = (bx - ax)*(bx - ax) + (by - ay)*(by - ay)
    if dotproduct > squaredlengthba:
        return False

    return True
    # IMPLEMENTATION A
    # startXA = 0
    # startXB = 0

    # startYA = 0
    # startYB = 0

    # # print x1, '_x1_'
    # # print x2, '_x2_'
    # # print xcoor, '_xcoor_'
    # # print ycoor, '_ycoor_'
    # # Check if intersection is contained on Line1
    # if x1 < x2:
    #   startXA = x1
    #   endXA = x2
    # elif x2 < x1:
    #   startXA = x2
    #   endXA = x1
    # else: # if they are equal
    #   if y1 < y2:
    #     startXA = x1
    #     endXA = x2
    #   elif y1 > y2:
    #     startXA = x2
    #     endXA = x1
    #   else:
    #     # not a line, this should never occur, but to be safe, return
    #     return

    
    # if y1 < y2:
    #   startYA = y1
    #   endYA = y2
    # elif y2 < y1:
    #   startYA = y2
    #   endYA = y1
    # else: # if they are equal
    #   if x1 < x2:
    #     startYA = y1
    #     endYA = y2
    #   elif x2 < x1:
    #     startYA = y2
    #     endYA = y1
    #   else:
    #     # not a line, this should never occur, but to be safe, return
    #     return

    # # if xcoor == 0 or ycoor == 0:
    # #   if not (xcoor == 0 and ycoor == 0): 
    # #       return Point(xcoor, ycoor)


    # if xcoor >= startXA and xcoor <= endXA:
    #   if ycoor >= startYA and ycoor <= endYA:

    #     # if xcoor >= startXB and xcoor <= endXB:
    #     #   if ycoor >= startYB and ycoor <= endYB:

    #         return True
    # else:
    #   return False
    # elif xcoor == 0 or ycoor == 0:
    #   return Point(xcoor, ycoor)
    # else:
    #   return


    # IMPLEMENTATION B


# def LineOnLine (l1, l2):
#     """Returns whether or not a line is in a line"""

#     x1, y1 = l1.src.x, l1.src.y
#     x2, y2 = l1.dst.x, l1.dst.y

#     xcoor = p1.x
#     ycoor = p1.y

#     startXA = 0
#     startXB = 0

#     startYA = 0
#     startYB = 0

#     # print x1, '_x1_'
#     # print x2, '_x2_'
#     # print xcoor, '_xcoor_'
#     # print ycoor, '_ycoor_'
#     # Check if intersection is contained on Line1
#     if x1 < x2:
#       startXA = x1
#       endXA = x2
#     elif x2 < x1:
#       startXA = x2
#       endXA = x1
#     else: # if they are equal
#       if y1 < y2:
#         startXA = x1
#         endXA = x2
#       elif y1 > y2:
#         startXA = x2
#         endXA = x1
#       else:
#         # not a line, this should never occur, but to be safe, return
#         return

    
#     if y1 < y2:
#       startYA = y1
#       endYA = y2
#     elif y2 < y1:
#       startYA = y2
#       endYA = y1
#     else: # if they are equal
#       if x1 < x2:
#         startYA = y1
#         endYA = y2
#       elif x2 < x1:
#         startYA = y2
#         endYA = y1
#       else:
#         # not a line, this should never occur, but to be safe, return
#         return

#     # if xcoor == 0 or ycoor == 0:
#     #   if not (xcoor == 0 and ycoor == 0): 
#     #       return Point(xcoor, ycoor)


#     if xcoor >= startXA and xcoor <= endXA:
#       if ycoor >= startYA and ycoor <= endYA:

#         # if xcoor >= startXB and xcoor <= endXB:
#         #   if ycoor >= startYB and ycoor <= endYB:

#             return True
#     else:
#       return False
#     # elif xcoor == 0 or ycoor == 0:
#     #   return Point(xcoor, ycoor)
#     # else:
#     #   return

    

def hasDigit(string):
    result = bool(re.search(r'\d', string))
    return result







def parser(Str):

  # ? = zero or one of
  # {1,} = one or more of

  # Neatly covers whitespace issue found at the beginning of the string
  Str = Str.strip()
  command = ()
  if Str:
    if not (Str[0]).isalpha():
      command = ()
      #print 'failed'
      message = "Error: Command must begin with an alphabetical character!"
      command = ('error', message, 'retry')
      return command 

    
    if Str == 'g' or Str.strip() == 'g':
      command = ('g','','')
      #print command,'__command__'
      return command

    command = ()

    # REMEMBER TO RETEST

    # elif not Str.endswith(')'):
    #   command = ()
    #   return command 

    # Remove Street
    #=======================================================
    
    try:
      if not Str:
        #print 'here'
        return command


      #pattern = re.compile('\s{0,}(a\s{1,}|c\s{1,}|r\s{1,}|g\s{1,})\s{1,}\"(.+?)\"\s{0,}')

      patternR = re.compile('\s{0,}(r\s{1,})\"(.+?)\"\s{0,}')


      matchR = re.match('\s{0,}(r\s{1,})\"(.+?)\"\s{0,}', Str)

      
      if patternR.match(Str) != None and (matchR.group(0) == Str):
        #print 'appropriate remove format entered'
        remAction = re.findall(r'^(r){1}\s',Str)
        remStreet = re.findall(r'\"(.+?)\"',Str)
        # print remAction
        # print remStreet
        # listA = list()
        # street = list()
        # print remAction,'remAction'
        # listA.append(remStreet)
        # street.append(listA)
        # print street
        # command = ()
        command = (remAction,remStreet,'removeStreet')
          #print 'commando'
        return command
        # nameSet = set()
        # if remStreet not in nameSet:
        #   command = (remAction,remStreet,'removeStreet')
        #   #print 'commando'
        #   return command
        # else:
        #   message = 'Error: Street cannot be found in Graph.'
        #   command = ('error',message,'incorrect')
        

      else:
        #print 'incorrect format'
        #return command
        #print 'foll'
        pass
    
    except:
      pass

  # except:# Exception as e:
  #     return command
    #============================================
  

  #command = ()

  # FORMAT CHECK
  #============================================
  try:
    #print '\nenter appropriate command'
    #Str = raw_input()
    if not Str:
      return command


    pattern = re.compile('\s{0,}(a\s{1,}|c\s{1,}|g\s{1,})\"(.+?)\"\s{1,}((\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\)\s{0,}){1,})')


    match = re.match('\s{0,}(a\s{1,}|c\s{1,}|g\s{1,})\"(.+?)\"\s{1,}((\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\)\s{0,}){1,})', Str)

    
    if pattern.match(Str) != None and (match.group(0) == Str):
      #print match.group(0)
      #print pattern.match(Str)
      #print 'appropriate format entered'
      pass

    else:
      #print 'incorrect format'
      return command

  # except:# Exception as e:
  #     return command
    #============================================

    # Ensure no unnecessary special characters are passed
    regex = re.compile('[@_!#$%^&*<>?/\|}{~]')  

    if(regex.search(Str) == None):
        pass
    else:
        command = ()
        #print 'failed'
        message = "Error: Special characters found, command rejected!"
        command = ('error', message, 'retry')
        return command 
        

    # search then findAll
    # if search doesn't equal

    findAction = re.findall(r'^(a|c|g){1}\s',Str)
    findStreet = re.findall(r'\"(.+?)\"\s',Str)
    #  old findCor
    #findCor = re.findall(r'\([+-]?\d{1,}\,[+-]?\d{1,}\)',Str)
    findCor = re.findall(r'\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\)',Str)
    
    # doesMatch = re.match(r'^(a|c|g){1}\s\"(.+?)\"\s(\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\))', Str)

    # # if doesMatch:
    # #   pass
    # # else:
    # #   print 'folly'
    # #   command = ()
    # #   return command

    # WHAT DOES RE.SEARCH DO
    # HOW TO ACTUALLY MATCH A STR WITH A REGEX

    # # ATTEMPT:                        ^
    # (r'(a|c|g){1}\s{1,}\"(.+?)\"\s{1,}(\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\))', Str)

    # Test on regex.com
    # Test it at the first with one coordinate
    # Then attempt to graduate from that

    # doMatch = re.match('^(a|c|g){1}\s','\"(.+?)\"\s','\(\s{0,}[+-]?\d{1,}\s{0,}\,\s{0,}[+-]?\d{1,}\s{0,}\)')

    # print doMatch.group(1)


    #  Very early check for various errors
    #  Due to findall implementation
    #  Reminder, this is not just to match the same number of brackets. 
    #  Findall does not account for something if it's a mess...hmm
    # brackX = '('
    # brackY = ')'
    
    countBracketsA = 0
    countBracketsB = 0

    if Str:
      for i in Str:
        if i == '(' or i == ')':
          countBracketsA += 1

      if findCor:
        for coor in findCor:
          for i in coor:
            if i == '(' or i == ')':
              countBracketsB += 1

      if countBracketsA != countBracketsB:
        #print countBracketsA
        #print countBracketsB
        command = ()
        #print 'failed'
        message = "Error: The command you entered is erroneous syntax!"
        command = ('error', message, 'retry')
        return command 

      #print Str
      newCounter = 0
      if Str:
        for i in Str:
          if i == ')':
            newCounter = 1
            #print 'showMe'
            continue
          if newCounter == 1:
            newCounter = 0
            if i!='(':
              space = re.match(r'\s', i)
              if not space:#i !=' ':#  replace with 0 or many spaces
                #print 'folly'
                message = "Error: The command you entered is erroneous syntax!"
                command = ('error', message, 'retry')
                return command





    #z = '"'
    # countQuotesA = 0
    # countQuotesB = 0

    # for i in Str:
    #   if i == z:
    #     countQuotesA += 1

    # if findStreet:
    #   for street in findStreet:
    #     for i in street:
    #       if i == z:
    #         countQuotesB += 1

    # if countQuotesA % 2 != 0 or (countQuotesA != countQuotesB):
    #   print countQuotesA
    #   print countQuotesB
    #   command = ()
    #   return command

    q = '"'
    countQs = 0
    if Str:
      for i in Str:
        if i == q:
          countQs += 1

    if countQs > 2:
      message = "Error: Only two double quotes should be entered!"
      command = ('error', message, 'retry')
      return command
      

    

    # for i in Str:
    #   if i == x or i == y:
    #     countBracketsA += 1

    # if findCor:
    #   for coor in findCor:
    #     for i in coor:
    #       if i == x or i == y:
    #         countBracketsB += 1

    # if countBracketsA != countBracketsB:
    #   print countBracketsA
    #   print countBracketsB
    #   command = ()
    #   return command

    # regex2 = re.compile('[@_!#$%^&*<>?/\|}{~:],.')
    # if(regex.search(findCor) == None):
    #     pass
    # else:
    #     command = ()
    #     return command

    
    #findAction[0] = findAction[0].strip
    #print findAction
    #print findAction,'findAction'
    #print findStreet,'findStreet'
    #print findStreet[0],'findStreet[0]'

    #print findAction[0],'findAction[0]'
    #print findStreet[0],'findStreet[0]'

    if not findStreet or not findCor:
        if Str == 'g' or Str.strip() == 'g':
            command = ('g','','')
            return command

    #if findAction:
    if findAction:
      if findAction[0] == 'g' and (findStreet or findCor):
        message = "Error: Graph command 'g' should be entered alone!"
        command = ('error', message, 'retry')
        return command
        

    if not findAction or not findStreet or not findCor:
        command = ()
        return command


    if findCor:
      if len(findCor) < 2:
          #print len(findCor)
          message = "Error: Not enough valid points provided!"
          command = ('error', message, 'retry')
          return command
    # elif (findAction and not findAction[0]) or (findStreet and not findStreet[0]) or (findCor and not findCor[0]):
    #     command = ()
    #     return command
    



    if findAction:
      if not(Str.startswith(findAction[0])):
        message = "Error: Commands should begin with (valid) actions!"
        command = ('error', message, 'retry')
        return command

    if len(findAction) != 1:
      message = "Error: Commands should begin with one valid action!"
      command = ('error', message, 'retry')
      return command

    if len(findStreet) != 1:
      message = "Error: Commands should contain only one (valid) street name!"
      command = ('error', message, 'retry')
      return command

    # #Redundant but shows how match works
    # #Checks to ensure there is a space after the action inputted
    # if not (re.match('^(a|c|g){1}\s', Str)):
    #   print 'no bueno/space'
    #   command = ()
    #   return command

    

    command = (findAction, findStreet, findCor)
    
    #  Strip white space appropriately from Street Name
    #  This is inappropriate now, hence removal
    #findStreet[0] = findStreet[0].strip()

    #  Check to ensure street name has no digit in it
    #if findStreet[0]:
    if findStreet:
      if hasDigit(findStreet[0]):
          message = "Error: Street names should not contain digits!"
          command = ('error', message, 'retry')
          return command

    if findAction:
      if len(findAction)>1:
          #print 'You have entered some part of your command incorrectly!'
          message = "Error: The command you entered is erroneous syntax!"
          command = ('error', message, 'retry')
          return command
      else:
        return command
    else:
        return command

    #print len(findCor),
    if findCor:
      if len(findCor) < 2:
          #print len(findCor)
          message = "Error: Not enough valid points provided to add or change a street!"
          command = ('error', message, 'retry')
          return command
      else:
          return command
    else:
        return command


  except:# Exception as e:
      #command = ()
      return command


def main():
    ### YOUR MAIN CODE GOES HERE
    curMap = Map()
    ### sample code to read from stdin.
    ### make sure to remove all spurious print statements as required
    ### by the assignment
    while True:
        line = sys.stdin.readline()
        if line == '':
            break
        elif line == '\n':
            break
        
        # else:
        #     chunk = fp.read(1)
        #     if chunk == '':
        #         break
        # print 'read a line:', line

        Str = line

        parsedStr = list(parser(Str))

        #print parsedStr
        if not parsedStr:
            #print 'Error: The command you entered is erroneous syntax.'
            sys.stdout.write('Error: The command you entered is erroneous syntax.\n')
            sys.stdout.flush()
            #i = 0# or continue
            continue
        elif parsedStr[0] == 'error':
            sys.stderr.write(parsedStr[1]+'\n')
            
            #i = 0
            continue
        elif parsedStr[0] == 'g':
            #  call graph method
            #print 'graph output'
            curMap.graph()
            #i = 0
            # UPDATE
            # break
            # UPDATE REVERTED
            continue
        else:
            #  remaining code goes here or pass
            pass

        if len(parsedStr) > 2:
          cmd, streetName, path = parsedStr[0], parsedStr[1], parsedStr[2]

        #  convert from list variables to string variables
        if cmd:
          cmd = cmd[0]

        #  WARNING, undo this if you see unexplainable issues
        streetName = streetName[0]
        #  WARNING, undo this if you see unexplainable issues


        if cmd == 'a':
            if curMap.uniqueStreet(streetName.lower()):
                curMap.addStreet(path, streetName.lower())
                #print 'Added', streetName,'!\n'
                #i = 0 
                continue
            else:
                message = "Error: You cannot add a street that already exists!"
                sys.stderr.write(message +'\n')

                #print
                #i = 0
                continue
        elif cmd == 'c':
            #print 'change'
            # REMOVE STREET
            result = curMap.removeStreet(streetName.lower())
            if result:
              #print result
              sys.stderr.write(result+'\n')
              #i=0
              continue
            # Naturally flows into 'else' below
            # ADD STREET
            if curMap.uniqueStreet(streetName.lower()):
                curMap.addStreet(path, streetName.lower())
                #print 'Added', streetName,'!\n'
                #i = 0 
                continue
            else:
                message = "Error: You cannot add a street that already exists!"
                sys.stderr.write(message +'\n')
                #print
                #i = 0
                continue

            
            #i = 0
            continue
        elif cmd == 'r':
          #print 'remove'
          result = curMap.removeStreet(streetName.lower())
          if result:
            #print result
            sys.stderr.write(result +'\n')
            # print
            #pass
          #i=0 
          continue

        # New updated line to exit on first pass
        break


    # print 'Finished reading input'
    # return exit code 0 on successful termination
    sys.exit(0)

if __name__ == '__main__':
    main()
