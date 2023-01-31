pipeline{
    agent none
    environment{
        TESTS_PATH='/build/tests'
        BUILD_PATH='/src/build'
        
        SDL2_TEST='test-sdl2/test-sdl2.sh'
        GLFW_TEST='test-glfw/test-glfw.sh'
        
        BUILD='build.sh'
    }
    stages{
        stage("Windows"){
            agent { label 'windows' } 
            steps{
                script{
                    sh '${BUILD_PATH}/${BUILD}'
                    // sh '${TESTS_PATH}/${GLFW_TEST}'
                }
            }
        }
        stage("Linux"){
            agent { label 'linux' } 
            steps{
                script{
                    sh '${BUILD_PATH}/${BUILD}'
                }
            }
        }
        stage("Web"){
            agent { label 'web' }
            steps{
                script{
                    sh '${BUILD_PATH}/${BUILD}'
                }
            }
        }
    }
}