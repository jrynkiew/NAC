pipeline{
    agent { label 'SDL Builder' } 
    environment{
        TESTS_PATH='/build/tests/'
        
        SDL2_TEST='test-sdl2/test-sdl2.sh'
        GLFW_TEST='test-glfw/test-glfw.sh'
    }
    stages{
        stage('calling tests script'){
            steps{
                script{
                    sh '${TESTS_PATH}/${SDL2_TEST}'
                    sh '${TESTS_PATH}/${GLFW_TEST}'
                }
            }
        }
    }
}