add_executable(netbuildertests
        WrapperTest.cpp
        WrapperTest.h
        LayerMakerTest.cpp
        LayerMakerTest.h
        NetBuilderTest.cpp
        NetBuilderTest.h
        AlexNetWeightLoaderTest.cpp
        AlexNetWeightLoaderTest.h)

#Link against netbuilder lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(netbuildertests catchtest netbuilder)

add_test(NAME netbuildertest COMMAND netbuildertests)
