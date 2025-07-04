document.addEventListener('DOMContentLoaded', () => {
    const calcButton = document.getElementById('calcButton');
    const str1Input = document.getElementById('str1');
    const str2Input = document.getElementById('str2');
    const resultDiv = document.getElementById('result');

    calcButton.addEventListener('click', async () => {
        const s1 = str1Input.value;
        const s2 = str2Input.value;

        // ボタンを無効化し、計算中メッセージを表示
        calcButton.disabled = true;
        resultDiv.innerHTML = '<p>計算中...</p>';

        try {
            // FlaskサーバーのAPIにリクエストを送信
            // このURLは、app.pyを実行しているサーバーのアドレスです
            const response = await fetch('https://lcs-i0t7.onrender.com/api/lcs', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ s1: s1, s2: s2 }),
            });

            if (!response.ok) {
                throw new Error(`サーバーエラー: ${response.status}`);
            }

            const data = await response.json();

            // 結果を表示
            resultDiv.innerHTML = `
                <p><strong>LCS:</strong> "${data.lcs}"</p>
                <p><strong>長さ:</strong> ${data.length}</p>
            `;

        } catch (error) {
            resultDiv.innerHTML = `<p style="color: red;">エラー: ${error.message}</p>`;
        } finally {
            // ボタンを再度有効化
            calcButton.disabled = false;
        }
    });
});
