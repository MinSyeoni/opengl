#pragma once

class CCamera;

class CRuntimeFrameWork
{
private:
	static CRuntimeFrameWork* mySelf;

private:
	GLint m_nViewPortWidth;
	GLint m_nViewPortHeight;
	GLboolean m_bGimbalLock{ true };

private:
	GLint m_fCurrentTime;
	GLfloat m_fPrevTime;
	GLint m_nCurrentFrame;

	// 행렬
	GLfloat m_mtxLocal[16]; // 4x4 행렬.



	Vector3D m_vRotate;

	CCamera*			m_pCamera{ nullptr };
public:
	CRuntimeFrameWork();
	~CRuntimeFrameWork() = default;

	GLvoid Init();
	GLvoid Update();
	GLvoid Render();
	GLvoid OnProcessKeyBoard(unsigned char key, int x, int y);
	GLvoid OnProcessSpecialKeyBoard(int key, int x, int y);
	GLvoid OnProcessMouse(int button, int state, int x, int y);
	GLvoid OnProcessMouseMove(int x, int y);
	GLvoid Reshape(int width, int height);

	static GLvoid UpdateCallback() {
		if (!mySelf) return GLvoid();
		mySelf->Update();
	}

	static GLvoid RenderCallback() {
		if (!mySelf) return GLvoid();
		mySelf->Render();
	}

	static GLvoid KeyBoardCallback(unsigned char key, int x, int y) {
		if (!mySelf) return GLvoid();
		mySelf->OnProcessKeyBoard(key, x, y);
	}

	static GLvoid SpecialKeyBoardCallback(int key, int x, int y) {
		if (!mySelf) return GLvoid();
		mySelf->OnProcessSpecialKeyBoard(key, x, y);
	}

	static GLvoid MouseCallback(int button, int state, int x, int y) {
		if (!mySelf) return GLvoid();
		mySelf->OnProcessMouse(button, state, x, y);
	}

	static GLvoid MouseMoveCallback(int x, int y) {
		if (!mySelf) return GLvoid();
		mySelf->OnProcessMouseMove(x, y);
	}

	static GLvoid ReshapeCallback(int w, int h) {
		if (!mySelf) return GLvoid();
		mySelf->Reshape(w, h);
	}
};
