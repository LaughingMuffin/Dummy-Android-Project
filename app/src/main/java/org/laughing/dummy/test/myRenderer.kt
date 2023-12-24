package org.laughing.dummy.test

import android.content.Context
import android.opengl.GLES30
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * Created by Seker on 7/2/2015.
 *
 *
 * Some code is uses from the OpenGL ES 3.0 programming guide second edition book.  used under the MIT license.
 *
 */
class myRenderer  //
    (context: Context?) : GLSurfaceView.Renderer {
    private var mWidth = 0
    private var mHeight = 0
    private var mAngle = 0f

    //used the touch listener to move the cube up/down (y) and left/right (x)
    var y = 0f
    var x = 0f

    // mMVPMatrix is an abbreviation for "Model View Projection Matrix"
    private val mMVPMatrix = FloatArray(16)
    private val mProjectionMatrix = FloatArray(16)
    private val mViewMatrix = FloatArray(16)
    private val mRotationMatrix = FloatArray(16)

    ///
    // Initialize the shader and program object
    //
    override fun onSurfaceCreated(glUnused: GL10, config: EGLConfig) {


        //set the clear buffer color to light gray.
        //GLES30.glClearColor(0.9f, .9f, 0.9f, 0.9f);
        //set the clear buffer color to a dark grey.
        GLES30.glClearColor(0.1f, .1f, 0.1f, 0.9f)
        //initialize the cube code for drawing.
        //if we had other objects setup them up here as well.
    }

    // /
    // Draw a triangle using the shader pair created in onSurfaceCreated()
    //
    override fun onDrawFrame(glUnused: GL10) {

        // Clear the color buffer  set above by glClearColor.
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT or GLES30.GL_DEPTH_BUFFER_BIT)

        //need this otherwise, it will over right stuff and the cube will look wrong!
        GLES30.glEnable(GLES30.GL_DEPTH_TEST)

        // Set the camera position (View matrix)  note Matrix is an include, not a declared method.
        Matrix.setLookAtM(mViewMatrix, 0, 0f, 0f, -3f, 0f, 0f, 0f, 0f, 1.0f, 0.0f)

        // Create a rotation and translation for the cube
        Matrix.setIdentityM(mRotationMatrix, 0)

        //move the cube up/down and left/right
        Matrix.translateM(mRotationMatrix, 0, x, y, 0f)

        //mangle is how fast, x,y,z which directions it rotates.
        Matrix.rotateM(mRotationMatrix, 0, mAngle, 1.0f, 1.0f, 1.0f)

        // combine the model with the view matrix
        Matrix.multiplyMM(mMVPMatrix, 0, mViewMatrix, 0, mRotationMatrix, 0)

        // combine the model-view with the projection matrix
        Matrix.multiplyMM(mMVPMatrix, 0, mProjectionMatrix, 0, mMVPMatrix, 0)

        //change the angle, so the cube will spin.
        mAngle += .4.toFloat()
    }

    // /
    // Handle surface changes
    //
    override fun onSurfaceChanged(glUnused: GL10, width: Int, height: Int) {
        mWidth = width
        mHeight = height
        // Set the viewport
        GLES30.glViewport(0, 0, mWidth, mHeight)
        val aspect = width.toFloat() / height

        // this projection matrix is applied to object coordinates
        //no idea why 53.13f, it was used in another example and it worked.
        Matrix.perspectiveM(mProjectionMatrix, 0, 53.13f, aspect, Z_NEAR, Z_FAR)
    }

    companion object {
        private const val TAG = "myRenderer"
        private const val Z_NEAR = 1f
        private const val Z_FAR = 40f

        ///
        // Create a shader object, load the shader source, and
        // compile the shader.
        //
        fun LoadShader(type: Int, shaderSrc: String?): Int {
            val shader: Int
            val compiled = IntArray(1)

            // Create the shader object
            shader = GLES30.glCreateShader(type)
            if (shader == 0) {
                return 0
            }

            // Load the shader source
            GLES30.glShaderSource(shader, shaderSrc)

            // Compile the shader
            GLES30.glCompileShader(shader)

            // Check the compile status
            GLES30.glGetShaderiv(shader, GLES30.GL_COMPILE_STATUS, compiled, 0)
            if (compiled[0] == 0) {
                Log.e(TAG, "Erorr!!!!")
                Log.e(TAG, GLES30.glGetShaderInfoLog(shader))
                GLES30.glDeleteShader(shader)
                return 0
            }
            return shader
        }

        /**
         * Utility method for debugging OpenGL calls. Provide the name of the call
         * just after making it:
         *
         * <pre>
         * mColorHandle = GLES30.glGetUniformLocation(mProgram, "vColor");
         * MyGLRenderer.checkGlError("glGetUniformLocation");</pre>
         *
         * If the operation is not successful, the check throws an error.
         *
         * @param glOperation - Name of the OpenGL call to check.
         */
        fun checkGlError(glOperation: String) {
            var error: Int
            while (GLES30.glGetError().also { error = it } != GLES30.GL_NO_ERROR) {
                Log.e(TAG, "$glOperation: glError $error")
                throw RuntimeException("$glOperation: glError $error")
            }
        }
    }
}