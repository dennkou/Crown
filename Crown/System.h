#pragma once
#ifndef CROWN_SYSTEM
#define CROWN_SYSTEM

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
		System();
		~System();

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

	private:
	};
}
#endif	//	CROWN