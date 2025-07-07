document.addEventListener('DOMContentLoaded', () => {
    // HTML の読み込みが完了してから実行
    const calcButton = document.getElementById('calcButton');
    const str1Input = document.getElementById('str1');
    const str2Input = document.getElementById('str2');
    const resultDiv = document.getElementById('result');
    const count1 = document.getElementById('count1');
    const count2 = document.getElementById('count2');
    const clear1Button = document.getElementById('clear1Button');
    const clear2Button = document.getElementById('clear2Button');

    const toggleBtn = document.getElementById('toggle-btn');
    const optionsDiv = document.getElementById('options-div');


    clear1Button.addEventListener('click', () => {
        str1Input.value = '';
        count1.textContent = '0 文字';
        str1Input.focus();
    });

    clear2Button.addEventListener('click', () => {
        str2Input.value = '';
        count2.textContent = '0 文字';
        str2Input.focus();
    });

    str1Input.addEventListener('input', () => {
        count1.textContent = `${str1Input.value.length} 文字`;
    });
    str2Input.addEventListener('input', () => {
        count2.textContent = `${str2Input.value.length} 文字`;
    });

    toggleBtn.addEventListener('click', () => {
            // 3. オプション表示をトグル（表示・非表示を切り替え）
            optionsDiv.hidden = !optionsDiv.hidden;

            // 4. 表示状態に応じてボタンのテキストを変更
            if (optionsDiv.hidden) {
                // 非表示の場合
                toggleBtn.textContent = '▶ オプション';
            } else {
                // 表示中の場合
                toggleBtn.textContent = '▼ オプション';
            }
    });


    calcButton.addEventListener('click', async () => {
        const s1 = str1Input.value;
        const s2 = str2Input.value;

        const isCppSelected = document.getElementById('radio-cpp').checked;
        
        // ボタンを無効化し、計算中メッセージを表示
        calcButton.disabled = true;
        resultDiv.innerHTML = '<p>計算中...</p>';

        try {
            url = '';

            if(isCppSelected){
                url = 'https://lcs2.onrender.com/api/lcs';
            }else{
                url = 'https://lcs-i0t7.onrender.com/api/lcs';
            }

            const response = await fetch(url, {
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
                <p><strong>長さ:</strong> ${data.length}</p>
                <p><strong>LCS:</strong> "${data.lcs}"</p>
            `;

        } catch (error) {
            resultDiv.innerHTML = `<p style="color: red;">エラー: ${error.message}</p>`;
        } finally {
            // ボタンを再度有効化
            calcButton.disabled = false;
        }
    });
});
