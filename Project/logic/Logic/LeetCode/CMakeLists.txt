#cmake file for module LeetCode
#author:XuPing
#created:2019/4/17 16:46:43

SET(LEETCODE
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/LeetCode.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/LeetCode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/AddingTwoNumber_2.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/AddingTwoNumber_2.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lrucache.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Lrucache.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/SkipList.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/SkipList.h"	
	"${CMAKE_CURRENT_SOURCE_DIR}/LanguageTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/LanguageTest.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/TreeNode.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/TreeNode.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/DynamicPlan.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/DynamicPlan.h"
	
)

IF(WIN32)
	INCLUDE_DIRECTORIES(
		${API_DIR}
		${PUBLIC_DIR}
		${THIRD_LIBRARIES_INCLUDE_DIR}/DbgHelp.h
        ${2D_DIR}
		${COMMON_TIME_DIR}
		${TINYXML_DIR}
		${LOGIC_INTERFACE_DIR}
		${LOGIC_DEFINE_DIR}
	)
ENDIF(WIN32)

IF(LINUX)
	INCLUDE_DIRECTORIES(
        ${API_DIR}
        ${PUBLIC_DIR}
        ${2D_DIR}
		${COMMON_TIME_DIR}
		${TINYXML_DIR}
		${LOGIC_INTERFACE_DIR}
		${LOGIC_DEFINE_DIR}
	)
ENDIF(LINUX)
MESSAGE(STATUS ${LOGIC_INTERFACE})
SOURCE_GROUP( Api	FILES ${API})
SOURCE_GROUP( Define FILES ${LOGIC_DEFINE})
SOURCE_GROUP( Public\\Tinyxml FILES ${TINYXML})
SOURCE_GROUP( Public\\2D FILES ${2D})
SOURCE_GROUP( Public\\time FILES ${COMMON_TIME})
SOURCE_GROUP( Public FILES ${PUBLIC})
SOURCE_GROUP( Interface FILES ${LOGIC_INTERFACE})
SOURCE_GROUP( \\ FILES ${LEETCODE})

IF(WIN32)
	SET(THIRD_LIB_DEBUG
		"${THIRD_LIBRARIES_DEBUG_DIR}/DbgHelp.Lib"
	)
	SET(THIRD_LIB_RELEASE
	)
ENDIF(WIN32)

IF(LINUX)

ENDIF(LINUX)

ADD_LIBRARY( LeetCode SHARED
	${PUBLIC}
	${API}
	${LOGIC_INTERFACE}
	${LOGIC_DEFINE}
	${TINYXML}
	${COMMON_TIME}
	${LEETCODE}
)

SET_PROPERTY(TARGET LeetCode PROPERTY FOLDER "Logic")

TARGET_LINK_LIBRARIES( LeetCode
	${KERNEL_LIBD}
	${KERNEL_LIB}
)