#pragma once
#ifndef CROWN_SYSTEM
#define CROWN_SYSTEM

#include "Object/Window.h"
#include "Object/RenderSystem/RenderSystem.h"

namespace Crown
{
	//================================================================================
	// 作成日 : 2023/6/27
	// 作成者 : 服部颯澄
	// 
	// 自作ライブラリ達全ての管理とアプリケーションへの橋渡しを行うよ☆
	// 
	//================================================================================
	class System final
	{
	public:
		~System();

		/// <summary>
		/// systemクラスへの唯一のポインタを返すよ☆
		/// </summary>
		/// <returns></returns>
		static System& GetInstance();

		/// <summary>
		/// エンジン全体の初期化を行うよ☆
		/// </summary>
		void Initialize();

		/// <summary>
		/// エンジン全体の更新を行うよ☆
		/// 定期的に呼び出す必要があるよ☆
		/// </summary>
		void Update();

		/// <summary>
		/// エンジン全体の終了処理を走らせるよ☆
		/// </summary>
		void Finalize();

		/// <summary>
		/// Crown全体が終了しようとしているのかを示すフラグを所得するよ☆
		/// </summary>
		/// <returns>trueで終了しようとしている</returns>
		inline bool GetEndFlag() const { return m_endFlag; }

		/// <summary>
		/// 描画エンジンを渡すよ☆
		/// </summary>
		/// <returns></returns>
		inline RenderObject::RenderSystem& GetRenderSystem() { return m_renderSystem; }

	private:
		System();
		System(System& system) = delete;
		System& operator=(System& crown) = delete;

		static std::unique_ptr<System> m_system;

		Window m_window;
		RenderObject::RenderSystem m_renderSystem;
		bool m_endFlag;
	};
}
#endif	//	CROWN